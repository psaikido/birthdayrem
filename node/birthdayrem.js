#!/usr/bin/env node

const util = require('util')

const fs = require('fs')
const homedir = require('os').homedir()
const birthdayFile = homedir + '/.config/birthdayrem/birthdays'
const people = []
const now = []


fs.readFile(birthdayFile, 'utf8', (err, data) => {
	if (err) {
		console.error(err)
		return
	}

	const rows = data.toString().split('\n');

	for (i in rows) {
		if (rows[i] != '') {
			people[i] = parseRows(rows[i])
		}
	}

	sortByDate()
	setNow()
	const p = sortHasHadBirthday()
	const pWithAges = calcAges(p)
	output(pWithAges)
});


function calcAges(peeps) {
	const ret = []

	for (i in peeps) {
		const p = peeps[i]

		ret[i] = p

		if (p['deathday'].length == 0) {
			if (p['hadBirthday']) {
				ret[i]['age'] = now['year'] - p['bYear']
			} else {
				ret[i]['age'] = (now['year'] - p['bYear']) - 1
			}

			ret[i]['next'] = ret[i]['age'] + 1
		} else {
			if (p['hadBirthday']) {
				ret[i]['age'] = p['dYear'] - p['bYear']
			} else {
				ret[i]['age'] = (p['dYear'] - p['bYear']) - 1
			}

			ret[i]['next'] = '-'
		}
	}

	return ret
}


function setNow() {
	const date = new Date();
    now['year'] = date.getUTCFullYear()
	now['month'] = date.getUTCMonth() + 1
	now['day'] = date.getUTCDate()
}


function sortHasHadBirthday() {
	const before = []
	const after = []
	const ret = []
	var countBefore = 0
	var countAfter = 0
	var countRet = 0

	for (i in people) {
		const p = people[i]
		p['hadBirthday'] = false

		if (p['bMonth'] < now['month']) {
			p['hadBirthday'] = true
			before[countBefore++] = p
		} else if (p['bMonth'] == now['month']) {
			if (p['bDay'] < now['day']) {
				p['hadBirthday'] = true
				before[countBefore++] = p
			} else {
				after[countAfter++] = p
			}
		} else {
			after[countAfter++] = p
		}
	}

	for (i = 0; i < countAfter; i++) {
		ret[countRet++] = after[i]
	}

	for (i = 0; i < countBefore; i++) {
		ret[countRet++] = before[i]
	}

	return ret
}


function sortByDate() {
	people.sort(function (a, b) {
		if (a['bMonth'] < b['bMonth']) {
			return -1
		} else if (a['bMonth'] == b['bMonth']) {
			if (a['bDay'] < b['bDay']) {
				return -1
			} else if (a['bDay'] == b['bDay']) {
				if (a['bYear'] < b['bYear']) {
					return -1
				} else {
					return 1
				}
			} else {
				return 1
			}
		} else {
			return 1
		}
	})
}


function parseRows(row) {
	const ret = [];
	const rowArray = row.split(',')

	ret['birthday'] = rowArray[0]

	const bArray = ret['birthday'].split('-')

	ret['bYear'] = bArray[0]
	ret['bMonth'] = bArray[1]
	ret['bDay'] = bArray[2]

	ret['name'] = rowArray[1].trim()

	if (rowArray[2]) {
		ret['deathday'] = rowArray[2]

		const dArray = ret['deathday'].split('-')

		ret['dYear'] = dArray[0]
		ret['dMonth'] = dArray[1]
		ret['dDay'] = dArray[2]
	} else {
		ret['deathday'] = ''
		ret['dYear'] = ''
		ret['dMonth'] = ''
		ret['dDay'] = ''
	}

	return ret
}


function output(ppl) {
	console.log('yyyy-mm-dd       NAME  AGE-NOW     NEXT')
	console.log('---------------------------------------')

	for (i in ppl) {
		const p = ppl[i]
		console.log(
			util.format(
				'%s %s %s %s', 
				p['birthday'], 
				p['name'].padStart(10),
				p['age'].toString().padStart(8),
				p['next'].toString().padStart(8),
			)
		)
	}
}
