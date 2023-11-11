#! /usr/bin/python

# Happy Birthday 'too yoo'.

from pathlib import Path
import operator
from datetime import date


class Tooyoo:
    def __init__(self):
        self.people = []
        self.today = date.today()

        pass

    def run(self):
        file = Path.home().joinpath(".config/birthdayrem/birthdays")
        data = open(file, "r")
        lines = data.readlines()

        for line in lines:
            line = line.replace("\n", "")
            person = self.parseLine(line)
            person['age'] = self.calcAge(person)

            if len(person['deathDate']) > 0:
                person['next'] = "-"
            else:
                person['next'] = person['age'] + 1

            self.people.append(person)

        self.reorder()
        self.output(self.people)

        data.close()

    def parseLine(self, line):
        pieces = line.split(',')
        birthday = pieces[0].split('-')

        person = {
            "year":  birthday[0],
            "month": birthday[1],
            "day": birthday[2],
            "name": pieces[1].strip(),
            "birthday": birthday,
        }

        if len(pieces) > 2:
            deathDate = pieces[2].split('-')
            person['deathDate'] = deathDate
            person["dYear"] = deathDate[0]
            person["dMonth"] = deathDate[1]
            person["dDay"] = deathDate[2]
        else:
            person['deathDate'] = ""
            person["dYear"] = ""
            person["dMonth"] = ""
            person["dDay"] = ""

        return person

    def output(self, people):
        print("yyyy-mm-dd {:>10} {:>8} {:>8}".format(
            "NAME", "AGE-NOW", "NEXT"))
        print("---------------------------------------")

        for person in people:
            print("{}-{}-{} {:>10} {:>8} {:>8}".format(
                person["year"],
                person["month"],
                person["day"],
                person["name"],
                person["age"],
                person["next"],
                )
            )

    def reorder(self):
        self.people = sorted(self.people,
                             key=operator.itemgetter('month', 'day', 'year'))

        after = []
        before = []

        for p in self.people:
            if int(p['month']) > self.today.month:
                after.append(p)
            elif int(p['month']) == self.today.month:
                if p['day'] >= self.today.day:
                    after.append(p)
                else:
                    before.append(p)
            else:
                before.append(p)

        self.people = after + before

        return

    def calcAge(self, person):
        calcYear = self.today.year
        birthYear = int(person['year'])
        birthMonth = int(person['month'])
        birthDay = int(person['day'])

        if len(person['dYear']) > 0:
            alive = False
            deathYear = int(person['dYear'])
            deathMonth = int(person['dMonth'])
            deathDay = int(person['dDay'])
        else:
            alive = True

        if alive is True:
            if birthMonth > self.today.month:
                calcYear -= 1
            elif birthMonth == self.today.month:
                if birthDay > self.today.day:
                    calcYear -= 1

            age = calcYear - birthYear
        else:
            if deathMonth > birthMonth:
                age = deathYear - birthYear
            elif deathMonth == birthMonth:
                if deathDay > birthDay:
                    age = deathYear - birthYear
                else:
                    age = (deathYear - birthYear) - 1
            else:
                age = (deathYear - birthYear) - 1

        return age


if __name__ == "__main__":
    Tooyoo().run()
