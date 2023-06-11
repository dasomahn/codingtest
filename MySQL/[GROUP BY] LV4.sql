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

-- 저자 별 카테고리 별 매출액 집계하기
-- 풀이 1
SELECT a.author_id, author_name, category, SUM(total) as TOTAL_SALES
FROM AUTHOR as a
NATURAL JOIN (    
    SELECT book_id, author_id, category, sum(sales) * price as total
    FROM BOOK_SALES
    NATURAL JOIN BOOK
    WHERE YEAR(sales_date) = 2022 and MONTH(sales_date) = 1
    GROUP BY book_id
) as T
GROUP BY author_id, category
ORDER BY a.author_id, category DESC

-- 풀이 2
SELECT author_id, author_name, category, sum(sales * price) as total_sales
FROM BOOK_SALES
NATURAL JOIN BOOK
NATURAL JOIN AUTHOR
WHERE YEAR(sales_date) = 2022 and MONTH(sales_date) = 1
GROUP BY author_id, category
ORDER BY author_id, category DESC

-- 년, 월, 성별 별 상품 구매 회원 수 구하기
SELECT YEAR(sales_date) as year, MONTH(sales_date) as month, gender, count(DISTINCT user_id) as users
FROM USER_INFO
NATURAL JOIN ONLINE_SALE
WHERE gender is not NULL
GROUP BY year, month, gender
ORDER BY year, month, gender