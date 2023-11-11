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
            "age": self.calcAge(line),
        }

        try:
            deathDate = pieces[2].split('-')
            person["dYear"] = deathDate[0]
            person["dMonth"] = deathDate[1]
            person["dDay"] = deathDate[2]
        except:
            person["dYear"] = ""
            person["dMonth"] = ""
            person["dDay"] = ""

        return person

    def output(self, people):
        print("yyyy-mm-dd {:>10} AGE".format("NAME"))
        print("-------------------------")

        for person in people:
            print("{}-{}-{} {:>10} {}".format(
                person["year"],
                person["month"],
                person["day"],
                person["name"],
                person["age"],
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
        print(person)
        return 0
        # calcYear = self.today.year
        #
        # if int(person['month']) > self.today.month:
        #     calcYear -= 1
        # elif int(person['month']) == self.today.month:
        #     if int(person['day']) > self.today.day:
        #         calcYear -= 1
        #
        # age = calcYear - int(person['year'])
        #
        # return age


if __name__ == "__main__":
    Tooyoo().run()
