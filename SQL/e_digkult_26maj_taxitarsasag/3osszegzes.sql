SELECT
	Concat(COUNT(fuvar.id), " fuvar es ", SUM(fuvar.tav), " km tavolsag") AS "3 napi osszegzes"
FROM
	fuvar;
