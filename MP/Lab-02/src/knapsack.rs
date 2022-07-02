use std::time::Instant;

use rand::{thread_rng, Rng};

use crate::combinations::CombiGen;

pub fn knapsack(
    n: usize,
    capacity: usize,
    items: &Vec<(usize, usize)>,
) -> Option<(usize, usize, Vec<usize>)> {
    if n > items.len() {
        return None;
    }

    let indexes = (0..n).collect();
    let mut generator = CombiGen::new(&indexes);

    let mut picked_cap = 0;
    let mut max_price = 0;
    let mut choice = vec![];

    if let Some(value) = generator.get_first() {
        let (temp_cap, temp_price) = value.iter().fold((0, 0), |mut acc, i| {
            acc.0 += items[**i].0;
            acc.1 += items[**i].1;
            acc
        });
        if temp_cap <= capacity {
            picked_cap = temp_cap;
            max_price = temp_price;
            choice = value.iter().map(|i| **i).collect();
        }
    } else {
        return None;
    }

    while let Some(value) = generator.get_next() {
        let (temp_cap, temp_price) = value.iter().fold((0, 0), |mut acc, i| {
            acc.0 += items[**i].0;
            acc.1 += items[**i].1;
            acc
        });

        if temp_cap > capacity {
            continue;
        }
        if temp_price > max_price {
            picked_cap = temp_cap;
            max_price = temp_price;
            choice = value.iter().map(|i| **i).collect();
        }
    }

    Some((picked_cap, max_price, choice))
}

pub fn measure_knapsack() {
    for c in 12..=20 {
        let mut items: Vec<(usize, usize)> = vec![];
        let mut rng = thread_rng();
        for _ in 0..c {
            items.push((rng.gen_range(10..=300), rng.gen_range(5..=55)));
        }
        let time = Instant::now();
        if let Some(opt) = knapsack(c, 300, &items) {
            let secs = time.elapsed().as_secs_f64();
            println!("Time elapsed for {} items: {} seconds", c, secs);
            println!("Price: {}, Weight: {}, Choice: {:?}", opt.1, opt.0, opt.2);
        } else {
            println!("Error!");
        }
    }
}

#[test]
fn test_knapsack() {
    let items = vec![(25, 625), (30, 300), (60, 1200), (20, 600)];

    let items_2 = vec![(10, 60), (20, 100), (30, 120)];

    assert_eq!(Some((85, 1825, vec![0, 2])), knapsack(4, 100, &items));

    assert_eq!(Some((50, 220, vec![1, 2])), knapsack(3, 50, &items_2));
}
