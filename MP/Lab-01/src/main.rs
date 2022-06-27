use std::time::Instant;
const CYCLE: usize = 1000000;
fn main() {
    let mut double_sum = 0.0;
    let mut int_sum = 0; 

    let mut rng = start();

    let clock = Instant::now();

    (0..CYCLE).for_each(|_|{
        double_sum += dget(&mut rng, -100.0, 100.0);
        int_sum += iget(&mut rng, -100, 100);
    });

    let time = clock.elapsed();

    println!("Количество циклов: {CYCLE}");
    println!("Среднее значение (i64): {}", int_sum as f64/ (CYCLE as f64));
    println!("Среднее значение (f64): {}", double_sum / (CYCLE as f64));
    println!("Продолжительность (сек): {}", time.as_secs_f64());
}

use rand::prelude::ThreadRng;
use rand::Rng;

fn start() -> ThreadRng {
    rand::thread_rng()
}

fn dget(rng: &mut ThreadRng, min: f64, max: f64) -> f64 {
    rng.gen_range(min..=max)
}

fn iget(rng: &mut ThreadRng, min: i64, max: i64) -> i64 {
    rng.gen_range(min..=max)
}