pub mod combinations;
pub mod permutations;

fn main() {
    let vec = vec![1, 2, 3, 4];
    let mut gen = combinations::CombiGen::new(&vec);
    gen.change_regime(combinations::CombiRegime::PARTLY(2));

    if let Some(first) = gen.get_first() {
        println!("{:?}", first);
        loop {
            let sub = gen.get_next();
            if sub.is_none() {
                break;
            }
            println!("{:?}", sub.unwrap());
        }
    } else {
        println!("Wrong params!");
    }

    let vec2 = vec![1, 2, 3, 4];
    let mut gen2 = permutations::PermGen::new(&vec2);
    gen2.change_regime(permutations::PermRegime::PARTLY(3));

    if let Some(first) = gen2.get_first() {
        println!("{:?}", first);
        loop {
            let sub = gen2.get_next();
            if sub.is_none() {
                break;
            }
            println!("{:?}", sub.unwrap());
        }
    } else {
        println!("Wrong params!");
    }
}
