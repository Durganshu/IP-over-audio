#include "ip-over-morse.h"

int who_am_i = TCP_CLIENT;
int port = DEFAULT_PORT;
char* address = DEFAULT_ADDRESS;

// bool sender = true;
// bool receiver = false;
// char* protocol = "TCP";

int main(int argc, char *argv[]) {
    /****************************************************************/
    // Take user input on whether to send/receive, 
    // protocol, port, address
    /****************************************************************/
    parse_args(argc, argv);
    
    /****************************************************************/
    // Initialize server/client
    /****************************************************************/
    if (who_am_i == UDP_CLIENT) {
        udp_start_client(address);
    }
    else if (who_am_i == UDP_SERVER) {
        udp_start_server();
    }
    else if (who_am_i == TCP_CLIENT) {
        tcp_start_client(address);
    }
    else {
        tcp_start_server();
    }

        
    while(1) {
        /****************************************************************/
        // Send/receive the message
        /****************************************************************/
        char message[MAX_SENTENCE_LENGTH];

        if (who_am_i == UDP_CLIENT) {
            udp_send(get_wav_file());
        }
            
        else if (who_am_i == UDP_SERVER) {
            udp_recv_request();
            udp_send_response();
            print_info_and_message(message);
        }
            
        else if (who_am_i == TCP_CLIENT) {
            tcp_send(get_wav_file());
        }
            
        else {
            tcp_handle_request();
            print_info_and_message(message);
        }

        /****************************************************************/
        // Ask the user if s/he wants to send/receive another message.
        // if yes, continue, else break.
        /****************************************************************/
        printf("Do you want to send/receive another message? (y/n): ");
        char c;
        scanf(" %c", &c);
        if(c == 'n') break;
    }
}

void print_help(char* prg, bool printHeader) {
    printf(" Options:\n"
	   "  -s / --send           send the message\n"
	   "  -r / --receive        receive the message\n"
	   "  -p / --port           specify port (default: 54321)\n"
	   "  -a / --address        specify destination address(default: 127.0.0.1)\n"
	   "  -pcl / --protocol     specify protocol: UDP or TCP (default: TCP)\n"
       "  -h / --help           print this help\n");

}

void parse_args(int argc, char* argv[]) {
    int arg=0;
    int is_client = 1;
    int is_tcp = 1;
    while(arg+1<argc)
    {
	    arg++;
	    if ((strcmp(argv[arg],"-h")==0) ||
	        strcmp(argv[arg],"--help")==0)
        {
            print_help(argv[0], true);
            exit(0);
        }

	    if ((strcmp(argv[arg],"-s")==0) ||
	        (strcmp(argv[arg],"--send")==0)) {
            is_client = 1;
            continue;
        }
    
	    if ((strcmp(argv[arg],"-r")==0) ||
	        (strcmp(argv[arg],"--receive")==0)) {
	        is_client = 0;
            continue;
        }
    
	    if (((strcmp(argv[arg],"-p")==0) ||
	        (strcmp(argv[arg],"--port")==0)) && (arg+1<argc)) {
	        arg++;     
	    	port = atoi(argv[arg]);
	        continue;
	    }
    
	    if (((strcmp(argv[arg],"-a")==0) ||
	        (strcmp(argv[arg],"--address")==0)) && (arg+1<argc)) {
	        arg++;
	    	address = argv[arg];
	        continue;
	    }
	    
        if (((strcmp(argv[arg],"-pcl")==0) ||
	        (strcmp(argv[arg],"--protocol")==0)) && (arg+1<argc)) {
            arg++;

            if (strcmp(argv[arg], "UDP")==0) {
                is_tcp = 0;
            }
            else if (strcmp(argv[arg], "TCP")==0) {
                is_tcp = 1;
            }
            else {
                printf("Invalid protocol. Please enter UDP or TCP.\n");
                exit(0);
            }

	        continue;
        }
    }

    if (is_client) {
        who_am_i = is_tcp ? TCP_CLIENT : UDP_CLIENT;
    }
    else {
        who_am_i = is_tcp ? TCP_SERVER : UDP_SERVER;
    }
}

char* get_wav_file() {
    printf("Enter a text file name to send: ");
    char* file_name = (char*)malloc(MAX_FILENAME*sizeof(char));
    scanf("%s", file_name);
    initialize_params(file_name);
    process_input();
    strcpy(params.output_file_name, params.input_file_name);
    char *wav_filename = process_output();

	for (int i = 0; i < MAX_CHARS; i++) {
		params.ascii_char = morse_table[i][0]; //For example, if i=1 than the variable 'ascii_char' contains 'B'.
		params.ascii_table[params.ascii_char] = i; // The 66-th ('B' in ASCII) element of the 'ascii_table' array contains 1.
	}
    create_wav_file();
    // Cleanup
    close_files();

    /* Play audio file */
    play_output();
    free(file_name);
    return wav_filename;
}

void decode_wav_file(char message[MAX_SENTENCE_LENGTH]) {
    read_wav_file();
    convert_wav_to_morse(message);
}

void print_info_and_message(char message[MAX_SENTENCE_LENGTH]) {
    printf("----------WAV File info----------\n");
    decode_wav_file(message);
    printf("----------The decoded message----------\n");
    printf("%s\n", message);
    printf("---------------------------------\n");
}