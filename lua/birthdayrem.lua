local home = os.getenv('HOME')
local File = io.lines(home .. '/.config/birthdayrem/birthdays')

local curYear = os.date("%Y")
local curMonth = os.date("%m")
local curDay = os.date("%d")


local function hasHadBirthday(sMonth, sDay, eMonth, eDay)
	if (sMonth < eMonth) then
		return true
	elseif (sMonth == eMonth) then
		if (sDay < eDay) then
			return true
		else
			return false
		end
	else
		return false
	end
end

local function parse(file)
	local lines = {}
	local person = {}
	local bYear, bMonth, bDay = "", "", ""
	local dYear, dMonth, dDay = "", "", ""
	local alive = true
	local hadBirthday = false

	for row in file do
		local birthday = string.match(row, "^(%g*),")
		bYear, bMonth, bDay = string.match(birthday, "^(%d*)-(%d*)-(%d*)")

		local name = string.match(row, "%g*,(%W%w+)")

		local deathday = string.match(row, "^%g*,%s%g*,%s(%g*)$")
		if deathday ~= nil then
			dYear, dMonth, dDay = string.match(deathday, "(%d*)-(%d*)-(%d*)")
			alive = false
			hadBirthday = hasHadBirthday(bMonth, bDay, dMonth, dDay)
		else
			dYear, dMonth, dDay = "", "", ""
			alive = true
			hadBirthday = hasHadBirthday(bMonth, bDay, curMonth, curDay)
		end


		person = {
			['name'] = name,
			['bYear'] = bYear,
			['bMonth'] = bMonth,
			['bDay'] = bDay,
			['dYear'] = dYear,
			['dMonth'] = dMonth,
			['dDay'] = dDay,
			['alive'] = alive,
			['hadBirthday'] = hadBirthday
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

local function calcAges(people)
	for _, p in pairs(people) do
		if (p.alive) then
			if (p.hadBirthday) then
				p.age = curYear - p.bYear
			else
				p.age = (curYear - p.bYear) - 1
			end

			p.next = p.age + 1 
		else
			if (p.hadBirthday) then
				p.age = p.dYear - p.bYear
			else
				p.age = (p.dYear- p.bYear) - 1
			end

			p.next = "-"
		end
	end

	return people
end

local function timeSort(people)
	local before = {}
	local after = {}
	local merge = {}

	for _, p in pairs(people) do
		if (p.hadBirthday) then
			table.insert(before, p)
		else
			table.insert(after, p)
		end
	end

	for _, p in pairs(after) do
		table.insert(merge, p)
	end

	for _, p in pairs(before) do
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
			p.bYear, p.bMonth, p.bDay, p.name, p.age, p.next
			)
		)
	end
end

local people = parse(File)
table.sort(people, dateCompare)
people = timeSort(people)
people = calcAges(people)
output(people)
