-- 없어진 기록 찾기
SELECT o.animal_id, o.name
FROM ANIMAL_OUTS as o
LEFT JOIN ANIMAL_INS as i ON o.animal_id = i.animal_id
WHERE i.animal_id is NULL
ORDER BY animal_id

-- 있었는데요 없었습니다
SELECT o.animal_id, o.name
FROM ANIMAL_OUTS as o
JOIN ANIMAL_INS as i ON o.animal_id = i.animal_id
WHERE o.datetime < i.datetime
ORDER BY i.datetime

-- 오랜 기간 보호한 동물(1)
SELECT i.name, i.datetime
FROM ANIMAL_INS as i
LEFT JOIN ANIMAL_OUTS as o ON i.animal_id = o.animal_id
WHERE o.animal_id is NULL
ORDER BY i.datetime LIMIT 3