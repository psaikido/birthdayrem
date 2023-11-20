#!/usr/bin/env node

const util = require('util')

const fs = require('fs')
const homedir = require('os').homedir()
const birthdayFile = homedir + '/.config/birthdayrem/birthdays'
const people = []


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

	output()
});


function parseRows(row) {
	const ret = [];
	const rowArray = row.split(',')

	ret['birthday'] = rowArray[0]
	ret['name'] = rowArray[1]

	if (rowArray[2]) {
		ret['deathday'] = rowArray[2]
	} else {
		ret['deathday'] = ''
	}

	return ret
}


function output() {
	for (i in people) {
		const p = people[i]
		console.log(
			util.format(
				'%s %s %s', 
				p['birthday'], 
				p['name']),
				p['deathday'],
		)
	}
}
