SELECT
	COUNT(*)
FROM
	hivatal
WHERE
	hivatal.mettol <= 1700
    AND hivatal.meddig >= 1601;
