-- 입양 시각 구하기(2)
-- 풀이 1
SET @hour = -1;
SELECT @hour as HOUR, 
    (SELECT COUNT(*)
     FROM ANIMAL_OUTS
     WHERE HOUR(datetime) = @hour) as COUNT
FROM ANIMAL_OUTS
WHERE (@hour := @hour + 1) < 24

-- 풀이 2
WITH RECURSIVE HOUR_TABLE as (
    SELECT 0 as hour
    UNION ALL
    SELECT hour+1 FROM HOUR_TABLE WHERE hour < 23
)

SELECT hour, COUNT(animal_id) as COUNT
FROM HOUR_TABLE
LEFT JOIN ANIMAL_OUTS on hour = hour(datetime)
GROUP BY hour