#!/usr/bin/awk -f

BEGIN {
	FS = ","

	now = strftime("%Y-%m-%d")
	split(now, nowBits, "-")
	thisYear = nowBits[1]
	thisMonth = nowBits[2]
	thisDay = nowBits[3]
	tmpYear = ""
	tmpMonth = ""
	tmpDay = ""

	printf("%s\n", formatRow("yyyy-mm-dd", "NAME", "AGE-NOW", "NEXT"))
	printf("%s\n", "---------------------------------------")

	count = 0

	PROCINFO["sorted_in"] = "@ind_num_asc"
}


{
	age = calcAge($1, now, $3)

	if (length($3) > 0) {
		bnext = "-"
	} else {
		bnext = age + 1
	}

	key = sprintf("%s-%d",tmpMonth tmpDay, tmpYear, count)
	row = sprintf("%s", formatRow($1, $2, age, bnext))

	if (isBefore($1, now)) {
		before[key] = row
	} else {
		after[key] = row
	}

	count += 1
}


END {
	count = 0

	for (i in after) {
		res[count] = after[i]
		count += 1
	}

	for (j in before) {
		res[count] = before[j]
		count += 1
	}

	for (k = 0; k < count; k++) {
		printf("%s\n", res[k])
	}
}


function isBefore(start, end) {
	split(start, arStart, "-")
	split(end, arEnd, "-")

	sMonth = arStart[2]
	eMonth = arEnd[2]

	sDay = arStart[3]
	eDay = arEnd[3]

	if (sMonth < eMonth) {
		return 1
	} else if (sMonth == eMonth) {
		if (sDay < eDay) {
			return 1
		} else {
			return 0
		}
	} else {
		return 0
	}
}


function calcAge(start, end, died) {
	split(start, arStart, "-")

	if (length(died) > 0) {
		split(died, arEnd, "-")
	} else {
		split(end, arEnd, "-")
	}

	sYear = arStart[1]
	eYear = arEnd[1]
	tmpYear = arStart[1]

	sMonth = arStart[2]
	eMonth = arEnd[2]
	tmpMonth = arStart[2]

	sDay = arStart[3]
	eDay = arEnd[3]
	tmpDay = arStart[3]

	# Are we later in the year?
	if (sMonth < eMonth) {
		return (eYear - sYear)
	} else if (sMonth == eMonth) {
		if (sDay < eDay) {
			return (eYear - sYear)
		} else {
			return (eYear - sYear) - 1
		}
	} else {
		return (eYear - sYear) - 1
	}
}

function formatRow(birthday, name, age, bnext) {
	return sprintf("%s %10s %8s %8s", birthday, name, age, bnext)
}

