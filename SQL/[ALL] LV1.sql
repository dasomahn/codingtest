-- SELECT > 조건에 부합하는 중고거래 댓글 조회하기
SELECT title, board_id, reply_id, r.writer_id, r.contents, DATE_FORMAT(r.created_date, '%Y-%m-%d')
FROM USED_GOODS_BOARD b
JOIN USED_GOODS_REPLY r USING (board_id)
WHERE DATE_FORMAT(b.created_date, "%Y-%m") = '2022-10'
ORDER BY r.created_date, title

-- String, Date > 자동차 대여 기록에서 장기/단기 대여 구분하기
SELECT history_id,
    car_id,
    DATE_FORMAT(start_date, '%Y-%m-%d'),
    DATE_FORMAT(end_date, '%Y-%m-%d'),
    CASE
        WHEN DATEDIFF(end_date, start_date)+1 >= 30 THEN '장기 대여'
        ELSE '단기 대여'
    END
    as 'RENT_TYPE'
FROM CAR_RENTAL_COMPANY_RENTAL_HISTORY
WHERE DATE_FORMAT(start_date, '%Y-%m') = '2022-09'
ORDER BY history_id DESC

-- String, Date > 특정 옵션이 포함된 자동차 리스트 구하기
SELECT *
FROM CAR_RENTAL_COMPANY_CAR
WHERE options LIKE '%네비게이션%'
ORDER BY car_id DESC

-- SELECT > 과일로 만든 아이스크림 고르기
SELECT flavor
FROM FIRST_HALF
NATURAL JOIN ICECREAM_INFO
WHERE ingredient_type = 'fruit_based'
GROUP BY FLAVOR
HAVING SUM(total_order) >= 3000
ORDER BY SUM(total_order) DESC