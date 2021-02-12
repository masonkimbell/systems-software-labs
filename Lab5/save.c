#include <stdio.h>
#include <time.h>

void find_day(int curr_day){
	if(curr_day == 0)
		printf("Thu ");
	else if(curr_day == 1)
		printf("Fri ");
	else if(curr_day == 2)
		printf("Sat ");
	else if(curr_day == 3)
		printf("Sun ");
	else if(curr_day == 4)
		printf("Mon ");
	else if(curr_day == 5)
		printf("Tue ");
	else if(curr_day == 6)
		printf("Wed ");
}

void find_month(int m){
	if(m == 0){
		printf("Jan ");
	}else if(m == 1){
		printf("Feb ");
	}else if(m == 2){
		printf("Mar ");
	}else if(m == 3){
		printf("Apr ");
	}else if(m == 4){
		printf("May ");
	}else if(m == 5){
		printf("Jun ");
	}else if(m == 6){
		printf("Jul ");
	}else if(m == 7){
		printf("Aug ");
	}else if(m == 8){
		printf("Sep ");
	}else if(m == 9){
		printf("Oct ");
	}else if(m == 10){
		printf("Nov ");
	}else if(m == 11){
		printf("Dec ");
	}
}

int main(){
	int t = time((time_t *)0); 
	t -= 10800 - 1020;
	printf("time: %d\n", t);

	//things to find:
	//day of week - done
	//month - done
	//day # - done
	//time: hh:mm:ss
	//year - done	
	
	//find day of week
	int d = t / 24 / 60 / 60;

	int curr_day = d % 7;
	find_day(curr_day);

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

	find_month(curr_month);
	
	//find day #
	printf("%d ", inmonth);
	
	//find time: hh:mm:ss
	int in_day = t - d*24*60*60;
	
	int h = in_day / 60 / 60;
	in_day -= h * 60 * 60;
	int m = in_day / 60;
	in_day -= m * 60;
	int s = in_day;
	if(h < 10){
		printf("0%d:", h);
	}else{
		printf("%d:", h);
	}
	if(m < 10){
		printf("0%d:", m);
	}else{
		printf("%d:", m);
	}if(s < 10){
		printf("0%d ", s);
	}else{
		printf("%d ", s);
	}

	printf("%d\n", curr_year);

	return 0;
}
