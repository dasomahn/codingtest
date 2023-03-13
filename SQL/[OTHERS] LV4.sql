-- SELECT > 서울에 위치한 식당 목록 출력하기
SELECT rest_id, rest_name, food_type, favorites, address, ROUND(AVG(review_score), 2) as score
FROM REST_INFO
NATURAL JOIN REST_REVIEW
WHERE LEFT(address, 2) = '서울'
GROUP BY rest_name
ORDER BY score DESC, favorites DESC

-- SELECT > 오프라인/온라인 판매 데이터 통합하기
-- 풀이1 (FULL OUTER JOIN)
SELECT DATE_FORMAT(sales_date, '%Y-%m-%d') as date, product_id, user_id, sales_amount
FROM ONLINE_SALE
NATURAL LEFT JOIN OFFLINE_SALE
WHERE YEAR(sales_date) = 2022 and MONTH(sales_date) = 3

UNION

SELECT DATE_FORMAT(sales_date, '%Y-%m-%d') as date, product_id, NULL as user_id, sales_amount
FROM ONLINE_SALE
NATURAL RIGHT JOIN OFFLINE_SALE
WHERE YEAR(sales_date) = 2022 and MONTH(sales_date) = 3

ORDER BY date, product_id, user_id

-- 풀이2 (UNION)
SELECT DATE_FORMAT(sales_date, '%Y-%m-%d') as date, product_id, user_id, sales_amount
FROM ONLINE_SALE
WHERE YEAR(sales_date) = 2022 and MONTH(sales_date) = 3

UNION

SELECT DATE_FORMAT(sales_date, '%Y-%m-%d') as date, product_id, NULL, sales_amount
FROM OFFLINE_SALE
WHERE YEAR(sales_date) = 2022 and MONTH(sales_date) = 3

ORDER BY date, product_id, user_id

-- Summer/Winter Coding(2019) > 우유와 요거트가 담긴 장바구니
-- 풀이 1
SELECT cart_id
FROM CART_PRODUCTS 
WHERE name in ('Milk', 'Yogurt')
GROUP BY cart_id
HAVING count(DISTINCT name) >= 2
ORDER BY cart_id

-- 풀이 2 (JOIN)
SELECT DISTINCT m.cart_id
FROM (
    SELECT cart_id
    FROM CART_PRODUCTS
    WHERE name = 'Milk'
) m
NATURAL JOIN (
    SELECT cart_id
    FROM CART_PRODUCTS
    WHERE name = 'Yogurt'
) y
ORDER BY cart_id

-- 풀이 3 (GROUP_CONCAT)
SELECT cart_id
FROM CART_PRODUCTS
GROUP BY cart_id
HAVING GROUP_CONCAT(DISTINCT name) like '%Yogurt%'
AND GROUP_CONCAT(DISTINCT name) like '%Milk%'
ORDER BY cart_id