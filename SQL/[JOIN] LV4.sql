-- 보호소에서 중성화한 동물
SELECT i.animal_id, i.animal_type, i.name
FROM ANIMAL_INS as i
JOIN ANIMAL_OUTS as o ON i.animal_id = o.animal_id
WHERE sex_upon_intake != sex_upon_outcome