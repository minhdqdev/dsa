void removeNewline(char *str){
    int i = 0;
    while(str[i] != '\0'){
        if(str[i] == '\n'){
            str[i] = '\0';
            break;
        }
        i++;
    }
}

void strip(char *str, char *result){
    // right strip
    int i=0;
    while(str[i] != '\0') i++;

    while(str[i-1] == ' ') i--;

    // left strip
    int j=0;
    while(str[j] == ' ') j++;

    strncpy(result, str+j, sizeof(char) * (i-j));
    result[i-j] = '\0';
}