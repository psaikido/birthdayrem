<?php

class BirthdayRem
{
	private $now;
	private $yearNow;
	private $monthNow;
	private $dayNow;

	public function __construct()
	{
		$today = getdate();
		$this->yearNow = $today['year'];
		$this->monthNow = $today['mon'];
		$this->dayNow = $today['mday'];
		$this->now = $this->yearNow . '-' . $this->monthNow . '-' . $this->dayNow;

		$birthdayFile = file($_SERVER['HOME'] . '/.config/birthdayrem/birthdays');
		$people = $this->parse($birthdayFile);
		$people = $this->sortInYear($people);
		list($before, $after) = $this->getBeforeAndAfter($people);
		$people = array_merge($after, $before);
		$this->output($people);
	}

	private function getBeforeAndAfter($people): array
	{
		$before = [];
		$after = [];

		foreach ($people as $person) {
			if ($person['bMonth'] < $this->monthNow) {
				array_push($before, $person);
			} else if ($person['bMonth'] == $this->monthNow) {
				if ($person['bDay'] <= $this->dayNow) {
					array_push($before, $person);
				} else {
					array_push($after, $person);
				}
			} else {
				array_push($after, $person);
			}
		}
		return [$before, $after];
	}

	private function parse($data): array
	{
		$people = [];
		$person = [];

		foreach ($data as $row) {
			$p = explode(",", $row);

			$birthday = explode("-", $p[0]);

			$person['bYear'] = $birthday[0];
			$person['bMonth'] = $birthday[1];
			$person['bDay'] = $birthday[2];

			$person['name'] = trim($p[1]);

			if (isset($p[2])) {
				$deathDay = explode("-", $p[2]);
				$person['death'] = $p[2];
				$person['age'] = $this->calcAge($birthday, $deathDay);
				$person['next'] = "-";
			} else {
				$person['death'] = "";
				$today = explode("-", $this->now);
				$person['age'] = $this->calcAge($birthday, $today);
				$person['next'] = $person['age'] + 1;
			}

			array_push($people, $person);
		}

		return $people;
	}

	private function calcAge($start, $end)
	{
		$sYear = (int)$start[0];
		$sMonth =(int) $start[1];
		$sDay = (int)$start[2];

		$eYear = (int)$end[0];
		$eMonth = (int)$end[1];
		$eDay = (int)$end[2];

		if ($sMonth < $eMonth) {
			$age = ($eYear - $sYear);
		} else if ($sMonth == $eMonth) {
			if ($sDay < $eDay) {
				$age = ($eYear - $sYear);
			} else {
				$age = ($eYear - $sYear) - 1;
			}
		} else {
			$age = ($eYear - $sYear) - 1;
		}

		return $age;
	}

	private function sortInYear($people): array
	{
		usort($people, [BirthdayRem::class, "sortMonthDay"]);

		return $people;
	}

	static function sortMonthDay($a, $b): int
	{
		if ($a['bMonth'] < $b['bMonth']) {
			return -1;
		} else if ($a['bMonth'] == $b['bMonth']) {
			if ($a['bDay'] < $b['bDay']) {
				return -1;
			} else if ($a['bDay'] == $b['bDay']) {
				if ($a['bYear'] < $b['bYear']) {
					return -1;
				} else {
					return 1;
				}
			} else {
				return 1;
			}
		} else {
			return 1;
		}
	}

	private function output($data): void
	{
		echo sprintf("%s-%s-%s %10s %8s %8s\n", 
			"yyyy",
			"mm",
			"dd",
			"NAME",
			"AGE-NOW",
			"NEXT",
		);

		echo "---------------------------------------\n";

		foreach ($data as $row) {
			echo sprintf("%s-%s-%s %10s %8s %8s\n", 
				$row['bYear'],
				$row['bMonth'],
				$row['bDay'],
				$row['name'],
				$row['age'],
				$row['next'],
			);
		}
	}
}

new BirthdayRem();
