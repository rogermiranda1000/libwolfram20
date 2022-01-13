/**
 * Permite la ejecución de programas en Linux
 * @author Roger Miranda
 */
#pragma once

#define _GNU_SOURCE		// execvpe
#include <unistd.h>
#include <sys/types.h> 	// pid_t
#include <sys/wait.h> 	// waitpid
#include <stdlib.h> 	// exit/EXIT_FAILURE
#include <string.h>		// strcpy/strcat
#include <stdbool.h>	// bool
#include <stdarg.h>		// va_list

#define FORK_SON 			0
#define CREATE_FORK_ERROR 	-1
#define WAIT_FORK_ERROR 	-2

#define ARGV_MAX_LEN		20
#define CMD_MAX_LEN			500

#define STATIC_STRING_LEN(str)	(sizeof(str)/sizeof(char))

typedef struct {
	int fd;			// FileDescriptor de la pipe
	bool type;		// Tipus de pipe (PIPE_LECTURA/PIPE_ESCRIPTURA)
} Pipe;

typedef struct {
	pid_t other_pid;	// en el fill indica el PID del pare, en el pare el PID del fill
	size_t pipe_num;	// nº de pipes
	Pipe *pipes;		// pipes
} ForkedPipeInfo;

/**
 * Llegeix del FileDescriptor fins trobar el delimitador i decideix si continuar o no
 * Útil per utilitzar junt amb '\n' com a stop_delimiter
 * /!\ El delimitador no es guarda al buffer, però sí s'elimina del FileDescriptor /!\
 * /!\ Cal fer el free del buffer /!\
 * @param fd					FileDescriptor on agafar les dades
 * @param buffer				Array on guardar la informació (amb '\0')
 * @param size					Caracters obtninguts (sense contar '\0'; NULL si no es vol guardar)
 * @param continue_delimiter	Caracter que marca quan parar la lectura
 * @param stop_delimiter		Caracter que marca quan parar la lectura
 * @retval true					S'ha detingut a continue_delimiter
 * @retval false				S'ha detingut a stop_delimiter
 */
bool readUntilAndContinue(int fd, char **buffer, size_t *size, char continue_delimiter, char stop_delimiter) {
	char aux;
	size_t s = 0;
	*buffer = NULL;
	
	while(read(fd, &aux, sizeof(char)) == sizeof(char) && aux != continue_delimiter && aux != stop_delimiter) {
		*buffer = (char*)realloc(*buffer, (s+1)*sizeof(char));
		(*buffer)[s++] = aux;
	}
	*buffer = (char*)realloc(*buffer, (s+1)*sizeof(char));
	(*buffer)[s] = '\0';
	
	if (size != NULL) *size = s;
	
	return (aux == continue_delimiter);
}

/**
 * Llegeix del FileDescriptor fins trobar el delimitador
 * /!\ El delimitador no es guarda al buffer, però sí s'elimina del FileDescriptor /!\
 * /!\ Cal fer el free del buffer /!\
 * @param fd		FileDescriptor on agafar les dades
 * @param buffer	Array on guardar la informació (amb '\0')
 * @param delimiter	Caracter que marca quan parar
 * @return			Caracters obtninguts (sense contar '\0')
 */
size_t readUntil(int fd, char **buffer, char delimiter) {
	size_t size;
	
	readUntilAndContinue(fd, buffer, &size, delimiter, delimiter);
	
	return size;
}

/**
 * Crea una copia del codi. El fill crida son_call i finalitza la execució,
 * mentre que al pare simplement se li retorna el PID del fill.
 * Si es vol cridar una funció en cas d'error es pot utilitzar error_call.
 * /!\ El pare ha d'esperar al fill amb waitpid /!\
 *
 * @param	freeMallocs		Funció que es cridarà en el cas del fill per alliberar els recursos del pare
 * @param	son_call		Funció que es cridarà en el cas del fill
 * @param	error_call		Funció que es cridarà en cas d'error
 * @return	0 si és el fill, -1 si error, si no és el PID del fill cap al pare
 *			[en principi, només es retornarà el PID del fill al pare;
 *			com a màxim retornarà -1 si error_call no fa exit]
 */
#define FORK_CODE(freeMallocs, son_call, error_call) ({	\
	int r = fork();										\
	if (r == -1) error_call;							\
	else if (r == FORK_SON) {							\
		/* fill -> cridar a la funció i sortir */		\
		if (freeMallocs != NULL) (*freeMallocs)();		\
		son_call;										\
		exit(0);										\
	}													\
														\
	r; /* return */										\
})


#define PIPE_READ	0
#define PIPE_WRITE	1

/**
 * Crea un fork, conectant pare i fill amb pipes
 * /!\ Cal destruir, tant en el pare com en el fill, el ForkedPipeInfo (freeForkedPipeInfo) /!\
 * /!\ Considerar les advertencies de FORK_CODE /!\
 * @param info			Resultat de getForkedPipeInfo; indica el número de pipes i les seves direccions
 * @param freeMallocs	Funció que es cridarà en el cas del fill per alliberar els recursos del pare
 * @param error_call	Funció que es cridarà en cas d'error
 * @param son_function	Nom de la funció a cridar pel fill.
 *						/!\ El primer argument ha de ser el ForkedPipeInfo que conecta amb el pare/!\
 * @param ...			La resta d'arguments a enviar a la funció del fill
 * @return				ForkedPipeInfo que conecta amb el fill
 */
#define PIPED_FORK(info, freeMallocs, error_call, son_function, ...) ({					\
	ForkedPipeInfo father_info = info;													\
	ForkedPipeInfo son_info = (ForkedPipeInfo){getpid(), father_info.pipe_num, NULL};	\
	son_info.pipes = (Pipe*)malloc(sizeof(Pipe)*father_info.pipe_num);					\
	if (son_info.pipes == NULL) { error_call; }											\
	for (size_t pipe_index = 0; pipe_index < father_info.pipe_num; pipe_index++) {		\
		int fd_pipe[2];																	\
		bool father_read = father_info.pipes[pipe_index].type;							\
		if (pipe(fd_pipe) == -1) { error_call; }										\
		son_info.pipes[pipe_index] = (Pipe){fd_pipe[!father_read], !father_read};		\
		father_info.pipes[pipe_index].fd = fd_pipe[father_read];						\
	}																					\
																						\
	father_info.other_pid = FORK_CODE(freeMallocs, {									\
		freeForkedPipeInfo(&father_info); /* tanca les pipes del fill que no utilitza */\
		son_function(son_info, __VA_ARGS__);											\
	}, error_call);																		\
																						\
	freeForkedPipeInfo(&son_info); /* tanca les pipes del pare que no utilitza */		\
	father_info; /* return */															\
})

/**
 * Obtè un ForkedPipeInfo (per concatenar-lo amb PIPED_FORK)
 * S'ha de destruir, però si s'utilitza en PIPED_FORK només cal destruir el ForkedPipeInfo del pare i el fill,
 * aquest es destruirà sol
 * @param 	pipe_num	Número de pipes a obrir
 * @param 	...		Tipus de les pipes (ex: 'PIPE_READ, PIPE_READ, PIPE_WRITE'). Vist des del punt de vista del pare
 * @return	ForkedPipeInfo a concatenar amb PIPED_FORK
 */
ForkedPipeInfo getForkedPipeInfo(size_t pipe_num, ...) {
	ForkedPipeInfo r = (ForkedPipeInfo){0,0,NULL};
	va_list list;
	
	r.pipes = (Pipe*)malloc(sizeof(Pipe)*pipe_num);
	if (r.pipes == NULL) return r;
	
	r.pipe_num = pipe_num;
	va_start(list, pipe_num);
	for(size_t n = 0; n < pipe_num; n++) {
		r.pipes[n] = (Pipe){-1,(bool)va_arg(list,int)};
	}
	va_end(list);
	
	return r;
}

/**
 * Tanca els FileDescriptors i fa els frees dels punters
 * @param info	ForkedPipeInfo a destruir
 */
void freeForkedPipeInfo(ForkedPipeInfo *info) {
	for (size_t n = 0; n < info->pipe_num; n++) close(info->pipes[n].fd);
	free(info->pipes);
	
	info->pipes = NULL;
	info->pipe_num = 0;
}

/**
 * Obtè el FileDescriptor d'un ForkedPipeInfo
 * @param info	ForkedPipeInfo on extreure el FileDescriptor
 * @param index	Index del FileDescriptor
 * @return		FileDescriptor d'info en la posició index
 */
int fdPipeInfo(ForkedPipeInfo info, size_t index) {
	return info.pipes[index].fd;
}

/**
 * Executa una comanda, bindejant abans el FD de sortida per pantalla cap a la pipe del fork
 * @param info	Pipe (argument establert automaticament per PIPED_FORK())
 * @param cmd	Comanda a executar
 * @param argv	Array d'argumentos a adjuntar amb la comanda (comanda incluida)
 *				/!\ Te que acabar en NULL /!\
 * @param envp	Array de variables d'usuari
 */
int runCommandWithPipe(ForkedPipeInfo info, char *cmd, char *argv[], char *envp[]) {
	if (dup2(fdPipeInfo(info, 0), 1) == -1) exit(1); // clona el FD de sortida per pantalla cap a la pipe del fork
	exit(execvpe(cmd, argv, envp));
}

/**
 * Ejecuta el comando 'cmd' con los argumentos 'argv' enviando todo el texto por la pipe dentro de pipe_info
 * @param pipe_info		Pipe donde leer el texto que el comando muestra por pantalla
 *						/!\ Tiene que liberarse con freeForkedPipeInfo() /!\
 * @param cmd			Comando a ejecutar
 * @param argv			Array de argumentos a adjuntar con el comando (comando incluido)
 *						/!\ Tiene que terminar en NULL /!\
 * @param envp			Array de variables de usuario
 * @param freeMallocs	Función para aliberar la memoria del padre al hacer el fork
 * @return		Retorno de la ejecución del hijo, o -1 si error al crear el fork
 */
int executeProgramWithPipe(ForkedPipeInfo *pipe_info, char *cmd, char *argv[], char *envp[], void (*freeMallocs)()) {
	int r = CREATE_FORK_ERROR;
	
	// obtiene la ruta absoluta
	char absolute_cmd[CMD_MAX_LEN];
	//strcpy(absolute_cmd, LINUX_PROGRAM_DIR);
	//strcat(absolute_cmd, cmd);
	strcpy(absolute_cmd, cmd);
	
	*pipe_info = PIPED_FORK(getForkedPipeInfo(1, PIPE_READ), freeMallocs,, runCommandWithPipe, /* arguments: */ absolute_cmd, argv, envp);
	if (pipe_info->other_pid != CREATE_FORK_ERROR) {
		if (waitpid(pipe_info->other_pid, &r, WUNTRACED | WCONTINUED) == -1) r = WAIT_FORK_ERROR;
	}
	
	return r;
}

/**
 * Ejecuta el comando 'cmd' con los argumentos separados por espacio
 * /!\ Solo 1 espacio, y no puede haber espacios en el inicio/final del comando /!\
 * @param pipe_info		Pipe donde leer el texto que el comando muestra por pantalla
 *						/!\ Tiene que liberarse con freeForkedPipeInfo() /!\
 * @param cmd			Comando a ejecutar
 * @param envp			Array de variables de usuario
 * @param freeMallocs	Función para aliberar la memoria del padre al hacer el fork
 * @return		Retorno de la ejecución del hijo, o -1 si error al crear el fork
 */
int executeProgramLineWithPipe(ForkedPipeInfo *pipe_info, char **cmd, char *envp[], void (*freeMallocs)()) {
	int r, size = 0;
	char *argv[ARGV_MAX_LEN], cpy_cmd[CMD_MAX_LEN];
	char *iter = cpy_cmd;
	
	// al fer el fork s'ha d'alliberar tota memoria del pare
	strcpy(cpy_cmd, *cmd);
	free(*cmd);
	*cmd = NULL;
	
	argv[size++] = iter;
	
	while (*iter != '\0') {
		if (*iter == ' ') {
			*iter = '\0';
			argv[size++] = iter+1;
		}
		iter++;
	}
	
	// l'últim element ha d'acabar en NULL
	argv[size++] = NULL;
	
	r = executeProgramWithPipe(pipe_info, argv[0], argv, envp, freeMallocs);
	
	return r;
}