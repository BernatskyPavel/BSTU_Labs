use permutations::PermGen;
use rand::{self, thread_rng, Rng};
use std::{
    f64::{INFINITY, NAN},
    time::Instant,
};

pub mod combinations;
pub mod permutations;

fn main() {
    for c in 5..=12 {
        let mut cities: Vec<Vec<f64>> = vec![];
        let mut rng = thread_rng();
        for i in 0..c {
            let mut row = vec![];
            for _ in 0..c {
                row.push(rng.gen_range(10.0f64..=300.0).trunc());
            }
            row[i] = INFINITY;
            cities.push(row);
        }

        for _ in 0..3 {
            cities[rng.gen_range(0..c)][rng.gen_range(0..c)] = INFINITY;
        }
        let time = Instant::now();
        if let Some(opt) = salesman(c, 1, &cities) {
            let secs = time.elapsed().as_secs_f64();
            println!("Time elapsed for {} cities: {} seconds", c, secs);
            println!("Sum: {}, Path: {:?}", opt.0, opt.1);
        } else {
            println!("Error!");
        }
    }
}

fn salesman(n: usize, origin: usize, matrix: &Vec<Vec<f64>>) -> Option<(f64, Vec<usize>)> {
    if matrix.len() != n || origin.saturating_sub(1) >= n {
        return None;
    }

    if !matrix.iter().all(|row| row.len() == n) {
        return None;
    }

    let array = &(0..n).collect();

    let mut generator = PermGen::new(array);

    let mut array: Vec<usize> = vec![];
    let mut min = if let Some(value) = generator.get_first() {
        array = value.iter().map(|x| **x).collect();
        (0..n).map(|i| matrix[*value[i]][*value[(i + 1) % n]]).sum()
    } else {
        NAN
    };

    if min.is_nan() {
        return None;
    } else {
        while let Some(value) = generator.get_next() {
            if *value[0] != origin.saturating_sub(1) {
                continue;
            }
            let sum = (0..n).map(|i| matrix[*value[i]][*value[(i + 1) % n]]).sum();
            if sum < min {
                min = sum;
                array = value.iter().map(|x| **x).collect();
            }
        }
    }

    Some((min, array))
}

#[test]
fn test_salesman() {
    let cities = vec![
        vec![0.0, 10.0, 15.0, 11.0, 2.0, 55.0],
        vec![17.0, 0.0, 16.0, 18.0, 21.0, 13.0],
        vec![10.0, 50.0, 0.0, 39.0, 22.0, 3.0],
        vec![28.0, 29.0, 24.0, 0.0, 28.0, 25.0],
        vec![27.0, 9.0, 32.0, 9.0, 0.0, 2.0],
        vec![43.0, 48.0, 40.0, 43.0, 21.0, 0.0],
    ];

    let cities_2 = vec![
        vec![0.0, 45.0, INFINITY, 25.0, 50.0],
        vec![45.0, 0.0, 55.0, 20.0, 100.0],
        vec![70.0, 20.0, 0.0, 10.0, 30.0],
        vec![80.0, 10.0, 40.0, 0.0, 10.0],
        vec![30.0, 50.0, 20.0, 10.0, 0.0],
    ];

    assert_eq!(
        Some((85.0, vec![0, 3, 2, 5, 4, 1])),
        salesman(6, 1, &cities)
    );

    assert_eq!(
        Some((120.0, vec![0, 3, 4, 2, 1])),
        salesman(5, 1, &cities_2)
    );
}
