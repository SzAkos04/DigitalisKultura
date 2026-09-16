SELECT
	(SELECT MIN(etkezes.datum) FROM etkezes) AS elso,
    (SELECT MAX(etkezes.datum) FROM etkezes) AS utolso;