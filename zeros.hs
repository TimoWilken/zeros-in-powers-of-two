module Main where

import Data.Foldable

digits :: Int -> Integer -> [Int]
digits _ 0 = []
digits base n = fromIntegral remainder : digits base rest
  where (rest, remainder) = divMod n $ fromIntegral base

digitToChar :: Int -> Char
digitToChar = (!!) $ ['0'..'9'] ++ ['a'..'z']

checkPowerOf2 :: Int -> Int -> IO Bool
checkPowerOf2 base expon = do
  let allDigits = digits base $ 2 ^ expon
      firstDigits = takeWhile (/= 0) allDigits
      hasZero = firstDigits /= allDigits
  putStr $ "2^" ++ show expon ++ ": "
  putStr $ map digitToChar firstDigits
  putStrLn $ if hasZero then "0..." else " -- contains no zeros!"
  return hasZero

main :: IO ()
main = for_ [30739014..] $ checkPowerOf2 10
