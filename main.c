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
	char* cmd = malloc(6 + strlen(file));
	strcpy(cmd, "code ");
	strcat(cmd, file);

	printf("====================\n");
	printf("Opening File with Visual Code\n");

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
	char *txt=malloc(strlen(name) + strlen("import static org.junit.Assert.*;\nimport org.junit.After;\nimport org.junit.Before;\nimport org.junit.Test;\n\npublic class {\n\t@Before\n\tpublic void setUp(){\n\t\t\n\t}\n\n\t@After\n\tpublic void tearDown(){\n\t\t\n\t}\n}") + 1);
	strcpy(txt, "import static org.junit.Assert.*;\nimport org.junit.After;\nimport org.junit.Before;\nimport org.junit.Test;\n\npublic class ");
	strcat(txt, name);
	strcat(txt, "{\n\t@Before\n\tpublic void setUp(){\n\t\t\n\t}\n\n\t@After\n\tpublic void tearDown(){\n\t\t\n\t}\n}");
	return txt;
}

void analizeOPR(int opr, char *name){
	char *file=malloc(strlen(name) + 6);
	strcpy(file, name);
	strcat(file, ".java");

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

void java(){
	int opr = -1;
	char buff[1024];
	
	printf("Type:\n  1-Class;\n  2-Abstract Class;\n  3-Interface;\n  4-Enum;\n  5-Unit Test;\n  6-Shell Script;\n  0-Back;\n\n$ ");
	scanf("%d", &opr);
	printf("====================\n");

	if(opr>6 || opr==-1){
		printf("Wrong Input\n");
		exit(0);
	}

	if(opr==0){
		menu();
	}

	if(opr==6){
		writeToFile("run.sh", "compile=\"javac $1\"\necho $compile\n$compile\n\nexec=\"java $2\"\necho $exec\n$exec\n\nclean=\"rm -f *.class\"\necho $clean\n$clean");
		execlp("chmod", "chmod", "0744", "run.sh", NULL);
	}

	printf("Name(without .java):\n$ ");
	scanf("%s", buff);

	char *name=(strdup(buff));

	analizeOPR(opr, name);
}

void flex(){
	char buff[1024];
	printf("Name(without .l):\n$ ");
	scanf("%s", buff);

	char *file=malloc(strlen(buff)+3);

	strcpy(file,buff);
	strcat(file,".l");

	char* txt = strdup("%{\n#include <stdio.h>\n%}\n\n%%\n\n%%\n\nint yywrap(){\n\treturn 1;\n}\n\nint main(){\n\tprintf(\"Inicio da filtragem\\n\");\n\tyylex();\n\tprintf(\"\\nFim da filtragem\\n\");\n\treturn 0;\n}");

	writeToFile(file, txt);
}

void c(){
	char buff[1024];
	printf("Name(without .c):\n$ ");
	scanf("%s", buff);

	char *file=malloc(strlen(buff)+3);

	strcpy(file,buff);
	strcat(file,".c");

	char* txt = strdup("#include <stdio.h>\n#include <stdlib.h>\n\nint main(int argc, char const *argv[]){\n\treturn 0;\n}");

	writeToFile(file, txt);
}

void gawk(){
	char buff[1024];
	printf("Name(without .gawk):\n$ ");
	scanf("%s", buff);

	char *file=malloc(strlen(buff)+6);

	strcpy(file,buff);
	strcat(file,".gawk");

	char* txt = strdup("BEGIN\t\t\t\t\t{ FS=\" \"; RS=\"\\n\" }\n\nEND\t\t\t\t\t\t{  }");

	writeToFile(file, txt);
}

void menu(){
	int opr = -1;

	printf("Language:\n  1-Java;\n  2-C;\n  3-Flex;\n  4-Gawk\n  0-Exit;\n\n$ ");
	scanf("%d", &opr);

	printf("====================\n");

	switch(opr){
		case 0:
			printf("Good Bye, my love!\n");
			exit(0);
			break;
		case 1:
			java();
			break;
		case 2:
			c();
			break;
		case 3:
			flex();
			break;
		case 4:
			gawk();
			break;
		default:
			printf("Wrong Input\n");
			break;
	}
}

int main(int argc, char const *argv[]){
	printf("====================\n");
	printf("     Welcome to\n");
	printf("        NewF\n");
	printf("====================\n");
	menu();
	return 0;
}

/*
exit(1)=>noArgs
exit(2)=>wrong input
exit(3)=>exit the app
*/