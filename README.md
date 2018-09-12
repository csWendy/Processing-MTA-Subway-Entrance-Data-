# Processing-MTA-Subway-Entrance-Data-
*****************************************************************************************
To run the program: 

step1:type "make" in terminal, 

step2:type "./project3 subway_entrances_cleaned_no_nullnames.csv commandfile1" in terminal. 
(You can replace commandfile1 with commandfile2 or commandfile3.)

command "make clean" or "make cleanall" for clearing all the executable files. 
******************************************************************************************

This project worked with a dataset consisting of all entrances and exits to the stations of New York City Transit Authority. The dataset is part of the New York City OpenData project and is provided by the Metropolitan Transit Authority(MTA).

The data set is visualized on a map at this URL: https://data.cityofnewyork.us/Transportation/Subway-Entrances/drex-xx56/data 

You can download it in CSV format with this link: https://data.cityofnewyork.us/api/views/he7q-3hwy/rows.csv?accessType=DOWNLOAD

###Documents and usage:###

subway_entrances_cleaned_no_nullnames.csv : a cleaned csv file containing all the dataset above. 

commandfile1: contains commands of 
"list_all_stations
list_entrances River Ave & 161st St at NE corner
list_entrances White Plains Rd & Pelham Pkwy at NE corner
list_entrances  3rd Ave & 53rd St at NE corner
list_entrances  7th Ave & 40th St at SE corner
"

commandfile2: contains commands of 
"list_line_stations  7
list_line_stations  E
list_line_stations  GS
list_line_stations  Q"

commandfile3: contains commands of
"nearest_entrance   -73.83094300   40.68487400
nearest_lines       -73.83094300   40.68487400
nearest_entrance    -73.99326200 40.72971
nearest_entrance   -73.9931      40.7294
nearest_station   -73.83094300   40.68487400
nearest_station    -73.99326200 40.72971
nearest_station    -73.99326200 40.72971
nearest_lines    -73.83094300   40.68487400
nearest_lines     -73.92534900 40.76221700"

Specific project description is in file "project3Description.pdf". It is written by Prof.Weiss of class CSCI33500 Software Analysis and Design III. 

command.h and command.o and Makefile are written by Prof.Weiss. 




