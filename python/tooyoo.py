#! /usr/bin/python

# Happy Birthday 'too yoo'.

from pathlib import Path


class Tooyoo:
    def __init__(self):
        pass

    def run(self):
        file = Path.home().joinpath(".config/birthdayrem/birthdays")
        data = open(file, "r")
        lines = data.readlines()

        for line in lines:
            line = line.replace("\n", "")
            arrLine = self.parseLine(line)
            print(arrLine)

        data.close()

    def parseLine(self, line):
        pieces = line.split(',')
        birthday = pieces[0].split('-')

        person = {
            "year":  birthday[0],
            "month": birthday[1],
            "day": birthday[2],
            "name": pieces[1].strip(),
        }

        try:
            deathDate = pieces[2].split('-')
            deathDate = {
                "dYear": deathDate[0],
                "dMonth": deathDate[1],
                "dDay": deathDate[2],
            }
        except:
            deathDate = {}

        return [person, deathDate]


if __name__ == "__main__":
    Tooyoo().run()
