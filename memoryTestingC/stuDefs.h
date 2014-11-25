/*
Name: Shaheen Ghazazani
www.shaiwanghazazani.com
*/

typedef struct {
  	char first[32];
  	char last[32];
  	int  age;
} PersonType;

typedef struct {
  	PersonType basicInfo;
  	char       stuNumber[12];
  	float      gpa;
} StudentType;

//CollegeTyp and IncomeType used in testing as an extra two structs of memory 
typedef struct {
		char schoolName[32];
		int ranking;	
		int numberOfStudents; 
} CollegeType;

typedef struct {
		float yearlyIncome;
		float yearTaxPayed;
		int numberOfJobs;
} IncomeType;

//below are HumanTesterOne, Two, and Three used a extras structs for testing. 

typedef struct {
	int tester1, tester2;
	char fName[MAX_STR];
	char lName[MAX_BLK];
} HumanTesterOne;

typedef struct {
	float complete1, complete2;
	char lastName[MAX_STR];
	int amountOfTimesTested;
} HumanTesterTwo; 

typedef struct {
	float vial1, vial2, vial3, vial4;
	char vialLables[MAX_STR];
	char vialCodes[MAX_STR];
	char vialLetter[C_TRUE];
} HumanTesterThree;
