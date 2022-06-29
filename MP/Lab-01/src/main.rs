use std::time::Instant;
const CYCLE: usize = 1_000_000;
fn main() {
    let mut double_sum: f64 = 0.0;
    let mut int_sum: i64 = 0;

    let mut rng: ThreadRng = start();

    let clock: Instant = Instant::now();

    for _ in 0..CYCLE {
        double_sum += dget(&mut rng, -100.0, 100.0);
        int_sum += iget(&mut rng, -100, 100);
    }

    let time: std::time::Duration = clock.elapsed();

    println!("Количество циклов: {CYCLE}");
    println!(
        "Среднее значение (i64): {}",
        int_sum as f64 / (CYCLE as f64)
    );
    println!("Среднее значение (f64): {}", double_sum / (CYCLE as f64));
    println!("Продолжительность (сек): {}", time.as_secs_f64());

    println!("Измерения для графика:");
    measure();
}

#[allow(unused)]
fn measure() {
    let mut double_sum: f64 = 0.0;
    let mut int_sum: i64 = 0;

    let mut rng: ThreadRng = start();

    for iter in 1..=15 {
        let cycle: i32 = iter * 1_000_000;
        let clock: Instant = Instant::now();

        for _ in 0..cycle {
            double_sum += dget(&mut rng, -100.0, 100.0);
            int_sum += iget(&mut rng, -100, 100);
        }

        let time: std::time::Duration = clock.elapsed();
        println!("Количество циклов: {cycle}");
        println!(
            "Среднее значение (i64): {}",
            int_sum as f64 / (cycle as f64)
        );
        println!("Среднее значение (f64): {}", double_sum / (cycle as f64));
        println!("Продолжительность (сек): {}", time.as_secs_f64());
    }
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
