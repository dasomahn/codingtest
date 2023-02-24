-- 조건에 맞는 도서와 저자 리스트 출력하기
# SELECT BOOK_ID, AUTHOR_NAME, DATE_FORMAT(PUBLISHED_DATE, '%Y-%m-%d')
# FROM BOOK as b, AUTHOR as a
# WHERE b.author_id = a.author_id and category = '경제'
# ORDER BY published_date

SELECT BOOK_ID, AUTHOR_NAME, DATE_FORMAT(PUBLISHED_DATE, '%Y-%m-%d')
FROM BOOK as b
JOIN AUTHOR as a ON b.author_id = a.author_id
WHERE category = '경제'
ORDER BY published_date

-- 상품 별 오프라인 매출 구하기
SELECT product_code, p.price * SUM(sales_amount) as SALES
FROM PRODUCT as p
JOIN OFFLINE_SALE as o ON p.product_id = o.product_id
GROUP BY o.product_id
ORDER BY SALES desc, product_code