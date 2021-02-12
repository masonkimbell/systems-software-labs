//Task3.c
//Mason Kimbell
//03/25/2020

//function myasctime works the same as char* asctime(const struct tm *timeptr)
//main runs the function and prints the output

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>

int convertIntToStr(char *str, int x){
	sprintf(str, "%d", x);
	return (strlen(str));
}

//copy old into new, assuming old and new have same size
void copyStr(char* old, char* new, int size){
	int i = 0;
	for(i = 0; i < size; i++){
		new[i] = old[i];
	}
	new[size] = '\0';
}

//copies day of week based on curr_day into day
void find_day(int curr_day, char* day){
	char b[3];
	if(curr_day == 0){
		char c[] = "Thu";
		copyStr(c, b, 3);
	}else if(curr_day == 1){
		char c[] = "Fri";
		copyStr(c, b, 3);
	}else if(curr_day == 2){
		char c[] = "Sat";
		copyStr(c, b, 3);
	}else if(curr_day == 3){
		char c[] = "Sun";
		copyStr(c, b, 3);
	}else if(curr_day == 4){
		char c[] = "Mon";
		copyStr(c, b, 3);
	}else if(curr_day == 5){
		char c[] = "Tue";
		copyStr(c, b, 3);
	}else if(curr_day == 6){
		char c[] = "Wed";
		copyStr(c, b, 3);
	}
	copyStr(b, day, 4);
}


void find_month(int m, char* month){
	char b[3];
	if(m == 0){
		char c[] = "Jan";
		copyStr(c, b, 3);
	}else if(m == 1){
		char c[] = "Feb";
		copyStr(c, b, 3);
	}else if(m == 2){
		char c[] = "Mar";
		copyStr(c, b, 3);
	}else if(m == 3){
		char c[] = "Apr";
		copyStr(c, b, 3);
	}else if(m == 4){
		char c[] = "May";
		copyStr(c, b, 3);
	}else if(m == 5){
		char c[] = "Jun";
		copyStr(c, b, 3);
	}else if(m == 6){
		char c[] = "Jul";
		copyStr(c, b, 3);
	}else if(m == 7){
		char c[] = "Aug";
		copyStr(c, b, 3);
	}else if(m == 8){
		char c[] = "Sep";
		copyStr(c, b, 3);
	}else if(m == 9){
		char c[] = "Oct";
		copyStr(c, b, 3);
	}else if(m == 10){
		char c[] = "Nov";
		copyStr(c, b, 3);
	}else if(m == 11){
		char c[] = "Dec";
		copyStr(c, b, 3);
	}

	copyStr(b, month, 3);
}

char* myasctime(const struct tm *timeptr){
	int t = timeptr; 
	//printf("time: %d\n", t);

	//things to find:
	//day of week - done, held in day[]
	//month - done, held in month[]
	//day # - done
	//time: hh:mm:ss - done
	//year - done	
	
	//find day of week
	int d = t / 24 / 60 / 60;

	int curr_day = d % 7;
	char day[4];
	find_day(curr_day, day);	

	//find year
	int y = d / 365;
	int curr_year = y + 1970;
	
	//find month
	int isleap = 0;
	if(curr_year % 4 == 0)
		isleap = 1;
	
	int days_before_curr_year = y*365 + y / 4;
	int inyear = d - days_before_curr_year + 1; 
	
	int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(isleap)
		days_in_month[1] += 1;

	int i;
	int inmonth = inyear;
	int curr_month = 0;
	for(i = 0; i < 12; i++){
		if(inmonth > days_in_month[i]){
			inmonth -= days_in_month[i];
			curr_month++;
		}else{
			break;
		}
	}

	char month[4];
	find_month(curr_month, month);
	
	//find day #
	char day_n[3];
	int day_n_len = convertIntToStr(day_n, inmonth);
	
	//find time: hh:mm:ss
	int in_day = t - d*24*60*60;
	
	int h = in_day / 60 / 60;
	in_day -= h * 60 * 60;
	int m = in_day / 60;
	in_day -= m * 60;
	int s = in_day;
	char hours[3];
	char minutes[3];
	char seconds[3];
	int h_len = convertIntToStr(hours, h);
	int m_len = convertIntToStr(minutes, m);
	int s_len = convertIntToStr(seconds, s);

	//find year
	char year[4];
	int y_len = convertIntToStr(year, curr_year);
	
	//write the time to a file
	//this makes it easy to combine the 7 segments into one string	
	char fname[] = "temp";
	char zero[] = "0";
	char space[] = " ";
	char colon[] = ":";
	char newline[] = "\n";
	int fd = open(fname, O_RDWR | O_CREAT, 0666);
	write(fd, day, 3);
	write(fd, space, 1);
	write(fd, month, 3);
	write(fd, space, 1);
	if(day_n_len == 1){
		write(fd, zero, 1);
	}
	write(fd, day_n, day_n_len);
	write(fd, space, 1);
	if(h_len == 1){
		write(fd, zero, 1);
	}
	write(fd, hours, h_len);
	write(fd, colon, 1);
	if(m_len == 1){
		write(fd, zero, 1);
	}
	write(fd, minutes, m_len);
	write(fd, colon, 1);
	if(s_len == 1){
		write(fd, zero, 1);
	}
	write(fd, seconds, s_len);
	write(fd, space, 1);
	write(fd, year, y_len);
	write(fd, newline, 1);
	//format: day mon dd hh:mm:ss year

	//will hold string to return
	char* time_str = malloc(25 * sizeof(char));
	//read string in file into buffer time_str
	//create temporary file and remove afterwards
	lseek(fd, 0, SEEK_SET);
	read(fd, time_str, 24);
	close(fd);

	//find path of temporary file	
	char cwd[100];
	if(getcwd(cwd, sizeof(cwd)) == NULL){
		printf("error");
	}
	int k = 0;
	while(cwd[k] != '\0')
		k++;
	cwd[k] = '/';
	k++;
	int j;
	for(j = 0; j < sizeof(fname); j++){
		cwd[k] = fname[j];
		k++;
	}
	cwd[k] = '\0';
	//done combining
	remove(cwd);
	time_str[24] = '\0';
	return time_str;
}

int main(){
	//est is 4 hours behind gmt
	printf("the current GMT time is %s\n", myasctime(time((time_t *)0)));
	printf("the current EST time is %s\n", myasctime(time((time_t *)0) - 4*3600));
	return 0;
}
