-- 상품을 구매한 회원 비율 구하기
SELECT YEAR(sales_date) as YEAR,
        MONTH(sales_date) as MONTH,
        COUNT(DISTINCT u.user_id) as PERCHASED_USERS,
        ROUND(COUNT(DISTINCT u.user_id) / (SELECT COUNT(*) FROM USER_INFO WHERE YEAR(joined) = 2021), 1) as PERCHASED_RATIO
FROM USER_INFO as u
JOIN ONLINE_SALE as o ON u.user_id = o.user_id
WHERE YEAR(joined) = 2021
GROUP BY YEAR, MONTH
ORDER BY YEAR, MONTH
