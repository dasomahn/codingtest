-- 대여 기록이 존재하는 자동차 리스트 구하기
SELECT DISTINCT car_id
FROM CAR_RENTAL_COMPANY_CAR 
NATURAL JOIN CAR_RENTAL_COMPANY_RENTAL_HISTORY
WHERE car_type = '세단' and MONTH(start_date) = 10
ORDER BY car_id DESC

-- 조건별로 분류하여 주문상태 출력하기
SELECT order_id, product_id, DATE_FORMAT(out_date, '%Y-%m-%d') as out_date,
    CASE
        WHEN out_date is NULL THEN '출고미정'
        WHEN out_date <= '2022-05-01' THEN '출고완료'
        ELSE '출고대기'
    END as 출고여부
FROM FOOD_ORDER
ORDER BY order_id

-- 오랜 기간 보호한 동물(2)
SELECT animal_id, o.name
FROM ANIMAL_OUTS as o
JOIN ANIMAL_INS as i USING (animal_id)
ORDER BY (o.datetime - i.datetime) DESC
LIMIT 2

-- 조회수가 가장 많은 중고거래 게시판의 첨부파일 조회하기
SELECT CONCAT('/home/grep/src/', board_id, '/', file_id, file_name, file_ext) AS FILE_PATH
FROM USED_GOODS_FILE 
WHERE board_id = (
    SELECT board_id
    FROM USED_GOODS_BOARD 
    ORDER BY views DESC
    LIMIT 1
)
ORDER BY file_id DESC

-- 조건에 맞는 사용자와 총 거래금액 조회하기
SELECT DISTINCT
    user_id,
    nickname,
    CONCAT(city, " ", street_address1, " ", street_address2) as 전체주소,
    CONCAT(LEFT(tlno, 3), '-', SUBSTR(tlno, 4, 4), '-', RIGHT(tlno, 4)) as 전화번호
FROM USED_GOODS_BOARD
JOIN USED_GOODS_USER ON writer_id = user_id
GROUP BY writer_id
HAVING COUNT(*) >= 3
ORDER BY user_id DESC