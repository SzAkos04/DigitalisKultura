SELECT
	CONCAT(SUM(IF(jatekos.neme = 1, 1, 0)), " férfi") AS ferfiak,
    CONCAT(SUM(IF(jatekos.neme = 0, 1, 0)), " nő") AS nok
FROM
	jatekos;