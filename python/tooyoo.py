#! /usr/bin/python

# Happy Birthday 'too yoo'.

from pathlib import Path


class Tooyoo:
    def __init__(self):
        self.people = []
        pass

    def run(self):
        file = Path.home().joinpath(".config/birthdayrem/birthdays")
        data = open(file, "r")
        lines = data.readlines()

        for line in lines:
            line = line.replace("\n", "")
            person = self.parseLine(line)
            self.people.append(person)

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
            print("{}-{}-{} {:>10}".format(
                person["year"], 
                person["month"],
                person["day"],
                person["name"]
                )
            )


if __name__ == "__main__":
    Tooyoo().run()
