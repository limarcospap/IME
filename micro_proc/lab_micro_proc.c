#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include "uartapi.c"
#include <time.h>

#define BUFFER_SIZE 1000

BOOL detect_question(char *string){
    int length = strlen(string);
    if (string[length-1] == '?') return TRUE;
    return FALSE;
}

void send_string(char *string){
    int i, length;
    char lf = 0x0A;
    char cr = 0x0D;
    length = strlen(string);

    for(i = 0; i < length; i++){
        while(!(envia_caracter_serial(&(string[i]))));
    }
    while(!(envia_caracter_serial(&cr)));
    while(!(envia_caracter_serial(&lf)));
}

void set_esp8266_server(void){
    char comandos[2][15] = { "AT+CIPMUX=1","AT+CIPSERVER=1"}, caractere;
    if(inicializa_serial("COM5", 8, ONESTOPBIT, NOPARITY, 115200, 1000)){
            send_string(comandos[0]);
            while(recebe_caracter_serial(&caractere));
            send_string(comandos[1]);
            while(recebe_caracter_serial(&caractere));
    }
    libera_serial();
}

int main(){
        int rand_num;
        int counter = 0, position_of_message, new_string_length, start, end;
        char caractere, buffer[BUFFER_SIZE], *new_string, send_command[50];
        char answers[4][17] = {"Yes", "No", "Maybe", "Weird question..."};
        srand(time(0));
        rand_num = rand()%4;
        set_esp8266_server();

         if(inicializa_serial("COM5", 8, ONESTOPBIT, NOPARITY, 115200, 1000)){
            printf("Waiting for connection...\n");
            while(!recebe_caracter_serial(&caractere));
            while(recebe_caracter_serial(&caractere));
            printf("Connection established!\n");
            printf("Send me your question, may I help you...\n");
            while(1){
                if(counter == BUFFER_SIZE || caractere == '?') {
                    buffer[counter] = '\0';
                    break;
                }
                if(recebe_caracter_serial(&caractere)){
                    buffer[counter] = caractere;
                    counter++;
                }

            }
             start = buffer - strchr(buffer, ':');
             end = strchr(buffer, '?') - buffer;
             new_string_length = end-start;
             new_string = (char*)malloc(new_string_length);

             strncpy(new_string, strchr(buffer, ':')+1, new_string_length);
             new_string[new_string_length+1]='\0';

            printf("The question is: %s\n", new_string);
            sprintf(send_command, "AT+CIPSEND=0,%d", strlen(answers[rand_num]));
            send_string(send_command);
            while(recebe_caracter_serial(&caractere));
            send_string(answers[rand_num]);
            while(recebe_caracter_serial(&caractere));
            send_string("AT+CIPSEND=0,4");
            while(recebe_caracter_serial(&caractere));
            send_string("Bye!");
            while(recebe_caracter_serial(&caractere));
            send_string("AT+CIPCLOSE=0");
            while(recebe_caracter_serial(&caractere));
            printf("Fim do programa\n");
         }
        libera_serial();
        return 0;
}


