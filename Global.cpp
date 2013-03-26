// Day of year
float day[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

float progress[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

float DAYS[9] = {100, 200, 365, 400, 500, 600, 700, 800, 900};
bool isTimeProgressing = false;

float getPlanetLocation(int planet) {
	return 2.0f * (planet + 1);
}

float speedFactor[10] = { 1.0f, .8f, .6f, .5f, .4f, .3f, .2f, .1f, .2f, 0.1f };

void updateDay(int planet) {
	float today = ++day[planet];
	if (today > DAYS[planet]) {
		day[planet] = 0;
	}
	progress[planet] = today / DAYS[planet];
}

void toggleTime() {
	isTimeProgressing = !isTimeProgressing;
}