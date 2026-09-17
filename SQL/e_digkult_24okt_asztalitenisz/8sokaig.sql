SELECT
	jatekos.nev,
	MAX(bajnok.ev) - MIN(bajnok.ev) AS kulonbseg
FROM
	bajnok
INNER JOIN
	jatekos ON bajnok.jatekos_id = jatekos.id
GROUP BY
	jatekos.id
HAVING
	kulonbseg >= 10 
ORDER BY kulonbseg DESC;