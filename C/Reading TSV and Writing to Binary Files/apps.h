#define   NUM_CATEGORIES  		 33
#define   NUM_RATINGS	  		  7
#define   HEADER_SIZE     		112
#define   MAX_LINE_SIZE   		300
#define   MAX_APP_NAME_SIZE   	200

#define	  TSV_FILENAME			"googlePlayStore.tsv"
#define	  BIN_FILENAME			"googlePlayStore.bin"

// App Categories and Names
char *Categories[NUM_CATEGORIES+1] = {
	"ART_AND_DESIGN","AUTO_AND_VEHICLES","BEAUTY","BOOKS_AND_REFERENCE","BUSINESS",
	"COMICS","COMMUNICATION","DATING","EDUCATION","ENTERTAINMENT","EVENTS","FAMILY",
	"FINANCE","FOOD_AND_DRINK","GAME","HEALTH_AND_FITNESS","HOUSE_AND_HOME",
	"LIBRARIES_AND_DEMO","LIFESTYLE","MAPS_AND_NAVIGATION","MEDICAL","NEWS_AND_MAGAZINES",
	"PARENTING","PERSONALIZATION","PHOTOGRAPHY","PRODUCTIVITY","SHOPPING","SOCIAL",
	"SPORTS","TOOLS","TRAVEL_AND_LOCAL","VIDEO_PLAYERS","WEATHER", ""};
#define	GAME	14
#define	WEATHER	32

						
char *CategoryNames[NUM_CATEGORIES+1] = {
	"Art & Design","Auto & Vehicles","Beauty","Books & Reference",
	"Business","Comics","Communication","Dating","Education","Entertainment",
	"Events","Family","Finance","Food & Drink","Games","Health & Fitness",
	"House & Home","Libraries & Demo","Lifestyle","Maps & Navigation","Medical",
	"News & Magazines","Parenting","Personalization","Photography", "Productivity", "Shopping",
	"Social","Sports","Tools","Travel & Local","Video Players","Weather","N/A"};

// App Content Ratings
char *ContentRatings[NUM_RATINGS] = {"Everyone","Everyone 10+","Teen","Mature 17+","Adults only 18+","Unrated", "N/A"};

#define	EVERYONE			0
#define	EVERYONE_10_PLUS	1
#define	TEEN				2
#define	MATURE_17_PLUS		3
#define	ADULTS_ONLY_18_PLUS	4
#define	UNRATED				5


// Months of the Year
char *Months[12] = {"Jan","Feb","Mar","Apr","May","Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

// app price types
#define   FREE					0
#define   PAID					1

// Struct to hold an app's data
typedef struct App {
  char            name[MAX_APP_NAME_SIZE];
  unsigned char   category;
  float           rating;
  unsigned int    reviews;
  unsigned int    size;			// in kilobytes
  unsigned int    installs;
  unsigned char   type;
  float			  price;
  unsigned char	  contentRating;
  unsigned short  year;
  unsigned char	  month;
  unsigned char   day;
} App;



