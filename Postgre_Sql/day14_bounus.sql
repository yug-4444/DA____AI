CREATE TABLE daily_trades(
    trade_id INT PRIMARY KEY,
	trade_date DATE NOT NULL,
	ticker TEXT NOT NULL,
	closing_price NUMERIC(10,2)NOT NULL,
	volume INT NOT NULL
);
INSERT INTO daily_trades VALUES
    (1, '2026-09-01', 'AAPL', 180.50, 5000),(2, '2026-09-01', 'TSLA', 240.00, 8000),(3, '2026-09-02', 'AAPL', 182.00, 6000),(4, '2026-09-02', 'TSLA', 235.00, 9500),(5, '2026-09-03', 'AAPL', 179.00, 7500),(6, '2026-09-03', 'TSLA', 238.00, 8200);

SELECT ticker,trade_date,closing_price,closing_price-LAG(closing_price,1,NULL)OVER(PARTITION BY ticker ORDER BY trade_date ASC,trade_id)AS change_price FROM daily_trades;

SELECT ticker,trade_date,volume,SUM(volume) OVER(PARTITION BY ticker ORDER BY trade_date ASC,trade_id ASC ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW)AS cumulative_volume FROM daily_trades;

WITH rank_trade as(SELECT ticker,trade_date,volume,DENSE_RANK()OVER(PARTITION BY ticker ORDER BY volume DESC)AS r_dense_rank FROM daily_trades)
SELECT ticker,trade_date,volume FROM rank_trade WHERE r_dense_rank=1;

SELECT ticker,trade_date,closing_price,LEAD(closing_price,1,0.0)OVER(PARTITION BY ticker ORDER BY trade_date ASC,trade_id ASC)AS next_day_price FROM daily_trades;

SELECT ticker,trade_date,closing_price,ROUND(AVG(closing_price)OVER(PARTITION BY ticker ORDER BY trade_date ASC,trade_id ASC ROWS BETWEEN 1 PRECEDING AND CURRENT ROW),2)AS moving_avg FROM daily_trades;