use rss::Channel;
use std::{error::Error, io};

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    loop {
        println!("1.Print list of students.\n2.Print list of notes of some student.\nAny other number to quit.\nPlease input your choice.");

        let mut choice = String::new();

        io::stdin()
            .read_line(&mut choice)
            .expect("Failed to read line");

        let choice = match choice.trim().parse::<usize>() {
            Ok(num) => num,
            Err(_) => continue,
        };

        println!("Your choice: {}", choice);

        match choice {
            1 => {
                let result = students_feed().await;
                if let Ok(channel) = result {
                    println!(
                        "Title: {}\nDescription: {}\n",
                        channel.title(),
                        channel.description()
                    );
                    channel.items().iter().for_each(|item| {
                        println!(
                            "Item: {}\nDescription: {}\n{}",
                            item.title().unwrap(),
                            item.description().unwrap(),
                            "-".repeat(25)
                        );
                    });
                } else {
                    let x = result.unwrap_err();
                    println!("{}", x.to_string());
                };
            }
            2 => {
                println!("Please input id of student.");
                let mut student_id = String::new();
                io::stdin()
                    .read_line(&mut student_id)
                    .expect("Failed to read line");

                let student_id = match student_id.trim().parse::<usize>() {
                    Ok(num) => num,
                    Err(_) => continue,
                };
                let result = notes_feed(student_id).await;
                if let Ok(channel) = result {
                    println!(
                        "Title: {}\nDescription: {}\n",
                        channel.title(),
                        channel.description()
                    );
                    channel.items().iter().for_each(|item| {
                        println!(
                            "Item: {}\nDescription: {}\n{}",
                            item.title().unwrap(),
                            item.description().unwrap(),
                            "-".repeat(25)
                        );
                    });
                } else {
                    let x = result.unwrap_err();
                    println!("{}", x.to_string());
                };
            }
            _ => {
                println!("Quit...");
                break;
            }
        }
    }
    Ok(())
}

async fn students_feed() -> Result<Channel, Box<dyn Error>> {
    let content =
        reqwest::get("http://localhost:789/PI-POIBMS-4/Lab-07/Lab_07.NotesFeed.svc/Students")
            .await?
            .bytes()
            .await?;
    let channel = Channel::read_from(&content[..])?;
    Ok(channel)
}

async fn notes_feed(student_id: usize) -> Result<Channel, Box<dyn Error>> {
    let content = reqwest::get(format!(
        "http://localhost:789/PI-POIBMS-4/Lab-07/Lab_07.NotesFeed.svc/Students?id={student_id}"
    ))
    .await?
    .bytes()
    .await?;
    let channel = Channel::read_from(&content[..])?;
    Ok(channel)
}
