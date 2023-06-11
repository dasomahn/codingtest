-- SELECT > 3월에 태어난 여성 회원 목록 출력하기
SELECT member_id, member_name, gender, DATE_FORMAT(date_of_birth, '%Y-%m-%d')
FROM MEMBER_PROFILE
WHERE MONTH(date_of_birth) = 3 and gender = 'W' and TLNO IS NOT NULL
ORDER BY member_id

-- SELECT > 재구매가 일어난 상품과 회원 리스트 구하기
-- 풀이 1 (GROUP)
SELECT user_id, product_id
FROM ONLINE_SALE
GROUP BY user_id, product_id
HAVING count(*) > 1
ORDER BY user_id, product_id DESC

-- 풀이 2 (SELF JOIN)
SELECT DISTINCT A.user_id, A.product_id
FROM ONLINE_SALE A JOIN ONLINE_SALE B
ON A.user_id = B.user_id and A.product_id = B.product_id and A.online_sale_id != B.online_sale_id
ORDER BY user_id, product_id DESC

-- IS NULL > NULL 처리하기
-- 풀이 1 (IFNULL)
SELECT animal_type,
    IFNULL(name, 'No name'),
    sex_upon_intake
FROM ANIMAL_INS

-- 풀이 2 (CASE)
SELECT animal_type,
    CASE
        WHEN (name is NULL) THEN 'No name'
        ELSE name
    END,
    sex_upon_intake
FROM ANIMAL_INS

-- 풀이 3 (COALESCE)
SELECT animal_type,
    COALESCE(name, 'No name'),
    sex_upon_intake
FROM ANIMAL_INS

-- String, Date > 자동차 평균 대여 기간 구하기
SELECT car_id,
    ROUND(AVG(DATEDIFF(end_date, start_date)+1), 1) as AVERAGE_DURATION
FROM CAR_RENTAL_COMPANY_RENTAL_HISTORY
GROUP BY car_id
HAVING average_duration >= 7
ORDER BY average_duration DESC, car_id DESC

-- String, Date > 조건에 부합하는 중고거래 상태 조회하기
SELECT board_id, writer_id, title, price,
    CASE
        WHEN status = 'SALE' THEN '판매중'
        WHEN status = 'RESERVED' THEN '예약중'
        WHEN status = 'DONE' THEN '거래완료'
    END as status
FROM USED_GOODS_BOARD
WHERE DATE_FORMAT(created_date, '%Y-%m-%d') = '2022-10-05'
ORDER BY board_id DESC