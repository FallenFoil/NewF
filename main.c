#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

static const char *fileContent[] = {
	//C
	"#include <stdio.h>\n#include <stdlib.h>\n\nint main(int argc, char const *argv[]){\n\treturn 0;\n}",
	//C++
	"#include <iostream>\n\nusing namespace std;\n\nint main(int argc, char const *argv[]){\n\tcout << \"Hello, World!\" << endl;\n\treturn 0;\n}",
	//Shell Script
	"#!/bin/bash\n\n",
	//Flex
	"%{\n#include <stdio.h>\n%}\n\n%%\n\n%%\n\nint yywrap(){\n\treturn 1;\n}\n\nint main(){\n\tyyin = fopen(\"file\", \"r\");\n\tprintf(\"Inicio da filtragem\\n\");\n\tyylex();\n\tprintf(\"\\nFim da filtragem\\n\");\n\treturn 0;\n}",
	//Gawk
	"BEGIN\t\t\t\t\t{ FS=\" \"; RS=\"\\n\" }\n\nEND\t\t\t\t\t\t{  }",
	//Java
	NULL
};

static const char *fileExtension[] = {
	//C
	"c",
	//C++
	"cpp",
	//Shell Script
	"sh",
	//Flex
	"flex",
	//Gawk
	"gawk"
};

void header();
void menu();

void writeToFile(char *file, int index){
	int fd=open(file, O_CREAT | O_TRUNC | O_WRONLY, 0744);
	write(fd, fileContent[index], strlen(fileContent[index]));
	close(fd);

	char* cmd = malloc(6 + strlen(file));
	strcpy(cmd, "code ");
	strcat(cmd, file);

	chmod(file, S_IRWXU);

	printf("\n\033[0;32mOpening File with Visual Code\033[0;0m\n");

	system(cmd);
}

char *class(char name[]){
	char *txt=malloc(strlen(name) + strlen("public class {\n	\n}") + 1);
	strcpy(txt, "public class ");
	strcat(txt, name);
	strcat(txt, "{\n	\n}");
	return txt;
}

char *abstract(char name[]){
	char *txt=malloc(strlen(name) + strlen("public abstract class {\n	\n}") + 1);
	strcpy(txt, "public abstract class ");
	strcat(txt, name);
	strcat(txt, "{\n	\n}");
	return txt;
}

char *interface(char name[]){
	char *txt=malloc(strlen(name) + strlen("public interface {\n	\n}") + 1);
	strcpy(txt, "public interface ");
	strcat(txt, name);
	strcat(txt, "{\n	\n}");
	return txt;
}

char *enums(char name[]){
	char *txt=malloc(strlen(name) + strlen("public enum {\n	\n}") + 1);
	strcpy(txt, "public enum ");
	strcat(txt, name);
	strcat(txt, "{\n	\n}");
	return txt;
}

char *unitTeste(char name[]){
	char *txt=malloc(strlen(name) + strlen("import static org.junit.Assert.*;\nimport org.junit.After;\nimport org.junit.Before;\nimport org.junit.Test;\n\npublic class {\n\t@Before\n\tpublic void setUp(){\n\t\t\n\t}\n\n\t@After\n\tpublic void tearDown(){\n\t\t\n\t}\n}") + 1);
	strcpy(txt, "import static org.junit.Assert.*;\nimport org.junit.After;\nimport org.junit.Before;\nimport org.junit.Test;\n\npublic class ");
	strcat(txt, name);
	strcat(txt, "{\n\t@Before\n\tpublic void setUp(){\n\t\t\n\t}\n\n\t@After\n\tpublic void tearDown(){\n\t\t\n\t}\n}");
	return txt;
}

void analizeOPR(int opr, char name[]){
	char *file=malloc(strlen(name) + 6);
	strcpy(file, name);
	strcat(file, ".java");

	switch(opr){
		case 1:
			fileContent[5] = class(name);
			break;
		case 2:
			fileContent[5] = abstract(name);
			break;
		case 3:
			fileContent[5] = interface(name);
			break;
		case 4:
			fileContent[5] = enums(name);
			break;
		case 5:
			fileContent[5] = unitTeste(name);
			break;
		default:
			break;
	}

	writeToFile(file, 5);
}

void java(){
	int opr = -1, read = 0;
	
	header();
	
	printf("\nType:\n  1) Class;\n  2) Abstract Class;\n  3) Interface;\n  4) Enum;\n  5) Unit Test;\n  0) Back;\n");
	
	while(opr < 0 || opr > 5){
		if(read != 0){
			printf("\033[0;31mWrong Input\033[0;0m\n");
		}

		printf("\n$ ");
		read = scanf("%d", &opr);
	}

	if(opr == 0){
		menu();
	}
	else{
		char buff[30];
		printf("Name(without .java):\n$ ");
		scanf("%30s", buff);

		analizeOPR(opr, buff);
	}
}

void ask4FileName(int index){
	char buff[30];
	printf("\nName (without .%s):\n$ ", fileExtension[index]);
	scanf("%30s", buff);

	char* file = malloc(strlen(buff) + strlen(fileExtension[index]) + 2); //The 2 represents the dot and the '\0' character

	strcpy(file, buff);
	strcat(file, ".");
	strcat(file, fileExtension[index]);

	writeToFile(file, index);
}

void header(){
	printf("====================\n");
	printf("     Welcome to\n");
	printf("        NewF\n");
	printf("====================\n");
}

void menu(){
	int opr = -1, read = 0;

	header();

	printf("\nLanguage:\n  1) C;\n  2) C++;\n  3) Java;\n  4) Shell Script;\n  5) Flex;\n  6) Gawk;\n  0) Exit;\n");

	while(opr < 0 || opr > 6){
		if(read != 0){
			printf("\033[0;31mWrong Input\033[0;0m\n");
		}

		printf("\n$ ");		
		read = scanf("%d", &opr);
	}

	switch(opr){
		case 0:
			printf("Good Bye, my love!\n");
			exit(0);
			break;
		case 1:
			ask4FileName(0);
			break;
		case 2:
			ask4FileName(1);
			break;
		case 3:
			java();
			break;
		case 4:
			ask4FileName(2);
			break;
		case 5:
			ask4FileName(3);
			break;
		case 6:
			ask4FileName(4);
			break;
		default:
			break;
	}
}

int main(int argc, char const *argv[]){
	menu();

	return 0;
}