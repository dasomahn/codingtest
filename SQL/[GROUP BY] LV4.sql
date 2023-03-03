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

-- 식품분류별 가장 비싼 식품의 정보 조회하기
SELECT category, price as MAX_PRICE, product_name
FROM (
    SELECT *, RANK() OVER (PARTITION BY category ORDER BY price DESC) as r
    FROM FOOD_PRODUCT
    WHERE category in ('과자', '국', '김치', '식용유')
) as T
WHERE r = 1
ORDER BY price DESC