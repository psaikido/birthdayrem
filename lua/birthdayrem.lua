local home = os.getenv('HOME')
local File = io.lines(home .. '/.config/birthdayrem/birthdays')

local curYear = os.date("%Y")
local curMonth = os.date("%m")
local curDay = os.date("%d")

local function parse(file)
	local lines = {}
	local person = {}
	local bYear, bMonth, bDay = "", "", ""
	local dYear, dMonth, dDay = "", "", ""

	for row in file do
		local birthday = string.match(row, "^(%g*),")
		bYear, bMonth, bDay = string.match(birthday, "^(%d*)-(%d*)-(%d*)")

		local name = string.match(row, "%g*,(%W%w+)")

		local deathday = string.match(row, "^%g*,%s%g*,%s(%g*)$")
		if deathday ~= nil then
			dYear, dMonth, dDay = string.match(deathday, "(%d*)-(%d*)-(%d*)")
		else
			dYear, dMonth, dDay = "", "", ""
		end

		person = {
			['name'] = name,
			['bYear'] = bYear,
			['bMonth'] = bMonth,
			['bDay'] = bDay,
			['dYear'] = dYear,
			['dMonth'] = dMonth,
			['dDay'] = dDay,
		}

		table.insert(lines, person)
	end

	return(lines)
end

local function dateCompare(a, b)
	if (a.bMonth < b.bMonth) then
		return true
	elseif (a.bMonth == b.bMonth) then
		if (a.bDay < b.bDay) then
			return true
		elseif (a.bDay == b.bDay) then
			if (a.bYear < b.bYear) then
				return true
			else
				return false
			end
		else
			return false
		end
	end

	return false
end

local function calcAge(sYear, eYear, dYear, after)
	local age = 0

	if (dYear ~= "") then
		if (after) then
			age = (dYear - sYear) - 1
		else
			age = dYear - sYear
		end
	else
		age = eYear - sYear
	end

	return age
end

local function calcNext(sYear, eYear, dYear)
	local next = ""

	if (dYear ~= "") then
		next = "-"
	else
		next = (eYear - sYear) + 1
	end

	return next
end

local function timeSort(people)
	local before = {}
	local after = {}
	local merge = {}

	for _, p in pairs(people) do
		if (p.bMonth < curMonth) then
			table.insert(before, p)
		elseif (p.bMonth == curMonth) then
			if (p.bDay < curDay) then
				table.insert(before, p)
			else
				table.insert(after, p)
			end
		else
			table.insert(after, p)
		end
	end

	for _, p in pairs(after) do
		p['age'] = calcAge(p.bYear, (curYear - 1), p.dYear, true)
		p['next'] = calcNext(p.bYear, (curYear - 1), p.dYear)
		table.insert(merge, p)

	end

	for _, p in pairs(before) do
		p['age'] = calcAge(p.bYear, curYear, p.dYear, false)
		p['next'] = calcNext(p.bYear, curYear, p.dYear)
		table.insert(merge, p)
	end

	return merge
end

local function output(people)
	print(string.format(
			"%4s-%2s-%2s %10s %8s %8s",
			"yyyy", "mm", "dd", "NAME", "AGE-NOW", "NEXT"
		)
	)

	print("---------------------------------------")

	for _, p in pairs(people) do
		print(string.format(
			"%4s-%2s-%2s %10s %8s %8s",
			p['bYear'], p['bMonth'], p['bDay'], p['name'], p['age'], p['next']
			)
		)
	end
end

local people = parse(File)
table.sort(people, dateCompare)
people = timeSort(people)
output(people)
