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

	printf("%s\n", formatRow("yyyy", "mm", "dd", "NAME", "AGE"))
	printf("%s\n", "-----------------------")

	count = 0
	countBefore = 0
	countAfter = 0
}


{
	age = calcAge($1, now)
	row = sprintf("%s", formatRow(tmpYear, tmpMonth, tmpDay, $2, age))

	if (isBefore($1, now)) {
		before[countBefore] = row
		countBefore += 1
	} else {
		after[countAfter] = row
		countAfter += 1
	}
}


END {
	for (i in after) {
		res[count] = after[i]
		count += 1
	}

	for (j in before) {
		res[count] = before[j]
		count += 1
	}

	for (k = 0; k < count; k++) {
		printf("%s %d\n", res[k], k)
	}
}

# function comp_func(i1, v1, i2, v2)
# {
#     # compare elements 1 and 2 in some fashion
#     # return < 0; 0; or > 0
#
# }

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


function calcAge(start, end) {
	split(start, arStart, "-")
	split(end, arEnd, "-")

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

function formatRow(y, m, d, name, age) {
	return sprintf("%s %s %s %7s %4s", y, m, d, name, age)
}

