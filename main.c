#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void menu();

void writeToFile(char *file, char *txt){
	int fd=open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	write(fd, txt, strlen(txt));
	close(fd);
	printf("Done!\n");
	char* cmd = malloc(6 + strlen(file));
	strcpy(cmd, "subl ");
	strcat(cmd, file);
	system(cmd);
}

char *class(char *name){
	char *txt=malloc(strlen(name) + strlen("public class {\n	\n}") + 1);
	strcpy(txt, "public class ");
	strcat(txt, name);
	strcat(txt, "{\n	\n}");
	return txt;
}

char *abstract(char *name){
	char *txt=malloc(strlen(name) + strlen("public abstract class {\n	\n}") + 1);
	strcpy(txt, "public abstract class ");
	strcat(txt, name);
	strcat(txt, "{\n	\n}");
	return txt;
}

char *interface(char *name){
	char *txt=malloc(strlen(name) + strlen("public interface {\n	\n}") + 1);
	strcpy(txt, "public interface ");
	strcat(txt, name);
	strcat(txt, "{\n	\n}");
	return txt;
}

char *enums(char *name){
	char *txt=malloc(strlen(name) + strlen("public enum {\n	\n}") + 1);
	strcpy(txt, "public enum ");
	strcat(txt, name);
	strcat(txt, "{\n	\n}");
	return txt;
}

char *unitTeste(char *name){
	char *txt=malloc(strlen(name) + strlen("import static org.junit.Assert.*;\nimport org.junit.After;\nimport org.junit.Before;\nimport org.junit.Test;\n\npublic class {\n	@Before\n	public void setUp(){\n        \n	}\n\n	@After\n	public void tearDown(){\n		\n	}\n}") + 1);
	strcpy(txt, "import static org.junit.Assert.*;\nimport org.junit.After;\nimport org.junit.Before;\nimport org.junit.Test;\n\npublic class ");
	strcat(txt, name);
	strcat(txt, "{\n	@Before\n	public void setUp(){\n        \n	}\n\n	@After\n	public void tearDown(){\n		\n	}\n}");
	return txt;
}

void analizeOPR(int opr, char *name){
	char *file=malloc(strlen(name) + 6);
	strcpy(file, name);
	strcat(file, ".java");
	printf("%s\n", file);

	switch(opr){
		case 1:
			writeToFile(file, class(name));
			break;
		case 2:
			writeToFile(file, abstract(name));
			break;
		case 3:
			writeToFile(file, interface(name));
			break;
		case 4:
			writeToFile(file, enums(name));
			break;
		case 5:
			writeToFile(file, unitTeste(name));
			break;
		default:
			break;
	}
}

void menu(){
	int opr;
	char buff[1024];

	printf("Type:\n1-Class;\n2-Abstract Class;\n3-Interface;\n4-Enum;\n5-Unit Test;\n6-Shell Script;\n0-Exit;\n");
	scanf("%d", &opr);
	
	if(opr>6){
		write(2,"Wrong Input\n", 13);
		exit(0);
	}

	if(opr==0){
		printf("Good Bye, my love!\n");
		exit(0);
	}

	if(opr==6){
		writeToFile("run.sh", "compile=\"javac $1\"\necho $compile\n$compile\n\nexec=\"java $2\"\necho $exec\n$exec\n\nclean=\"rm -f *.class\"\necho $clean\n$clean");
		execlp("chmod", "chmod", "0744", "run.sh", NULL);
	}

	printf("Name(without .java):\n");
	scanf("%s", buff);

	char *name=(strdup(buff));

	analizeOPR(opr, name);
}

int main(int argc, char const *argv[]){

	menu();

	return 0;
}

/*
exit(1)=>noArgs
exit(2)=>wrong input
exit(3)=>exit the app
*/