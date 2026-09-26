SELECT
	szinkron.szerep,
    szinkron.szinesz,
    szinkron.hang
FROM
	szinkron
WHERE szinkron.szerep LIKE "%rab%";