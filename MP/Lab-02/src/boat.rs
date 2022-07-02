use std::time::Instant;

use rand::{thread_rng, Rng};

use crate::combinations::{CombiGen, CombiRegime};
use crate::knapsack::knapsack;
use crate::permutations::{PermGen, PermRegime};

pub fn boat(
    n: usize,
    c: usize,
    capacity: usize,
    items: &Vec<(usize, usize)>,
) -> Option<(usize, usize, Vec<usize>)> {
    if n > items.len() {
        return None;
    }

    if c >= n {
        return knapsack(n, capacity, items);
    }

    let indexes = (0..n).collect();
    let mut generator = CombiGen::new(&indexes);
    generator.change_regime(CombiRegime::PARTLY(c));

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

pub fn measure_boat() {
    for c in 25..=35 {
        let mut items: Vec<(usize, usize)> = vec![];
        let mut rng = thread_rng();
        for _ in 0..c {
            items.push((rng.gen_range(100..=900), rng.gen_range(10..=150)));
        }
        let time = Instant::now();
        if let Some(opt) = boat(c, 6, 1500, &items) {
            let secs = time.elapsed().as_secs_f64();
            println!("Time elapsed for {} containers: {} seconds", c, secs);
            println!("Price: {}, Weight: {}, Choice: {:?}", opt.1, opt.0, opt.2);
        } else {
            println!("Error!");
        }
    }
}

pub fn boat_c(
    n: usize,
    c: usize,
    items: &Vec<(usize, usize)>,
    places: &Vec<(usize, usize)>,
) -> Option<(usize, Vec<usize>)> {
    if n > items.len() || c > places.len() {
        return None;
    }

    let indexes = (0..n).collect();
    let mut generator = PermGen::new(&indexes);
    generator.change_regime(PermRegime::PARTLY(c));

    let mut max_price = 0;
    let mut choice = vec![];

    if let Some(value) = generator.get_first() {
        let (temp_price, is_valid) = value.iter().enumerate().fold((0, true), |mut acc, i| {
            acc.0 += items[**i.1].1;
            acc.1 &= items[**i.1].0 >= places[i.0].0 && items[**i.1].0 <= places[i.0].1;
            acc
        });

        if is_valid {
            max_price = temp_price;
            choice = value.iter().map(|i| **i).collect();
        }
    } else {
        return None;
    }

    while let Some(value) = generator.get_next() {
        let (temp_price, is_valid) = value.iter().enumerate().fold((0, true), |mut acc, i| {
            acc.0 += items[**i.1].1;
            acc.1 &= items[**i.1].0 >= places[i.0].0 && items[**i.1].0 <= places[i.0].1;
            acc
        });

        if is_valid {
            max_price = temp_price;
            choice = value.iter().map(|i| **i).collect();
        }
    }

    Some((max_price, choice))
}

pub fn measure_boat_c() {
    for c in 4..=8 {
        let mut items: Vec<(usize, usize)> = vec![];
        let mut places: Vec<(usize, usize)> = vec![];
        let mut rng = thread_rng();
        for _ in 0..10 {
            items.push((rng.gen_range(100..=200), rng.gen_range(10..=100)));
        }

        for _ in 0..c {
            places.push((rng.gen_range(50..=120), rng.gen_range(150..=850)));
        }

        let time = Instant::now();
        if let Some(opt) = boat_c(10, c, &items, &places) {
            let secs = time.elapsed().as_secs_f64();
            println!("Time elapsed for {} places: {} seconds", c, secs);
            println!("Price: {}, Choice: {:?}", opt.0, opt.1);
        } else {
            println!("Error!");
        }
    }
}

#[test]
fn test_boat() {
    let items = vec![
        (100, 10),
        (200, 15),
        (300, 20),
        (400, 25),
        (500, 30),
        (150, 25),
    ];

    //let items_2 = vec![(10, 60), (20, 100), (30, 120)];

    assert_eq!(Some((950, 75, vec![2, 4, 5])), boat(6, 3, 1000, &items));

    //assert_eq!(Some((50, 220, vec![1, 2])), boat(3, 50, &items_2));
}

#[test]
fn test_boat_c() {
    let items = vec![(100, 10), (200, 15), (300, 20), (400, 25)];

    let places = vec![(350, 750), (250, 350), (0, 750)];

    //let items_2 = vec![(10, 60), (20, 100), (30, 120)];

    assert_eq!(Some((60, vec![3, 2, 1])), boat_c(4, 3, &items, &places));

    //assert_eq!(Some((50, 220, vec![1, 2])), boat(3, 50, &items_2));
}
