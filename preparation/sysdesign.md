# Key Steps for System Design Interview:

## Understand the Problem:

- Begin by asking basic questions to clarify the system's purpose until you can clearly define the core functionality.
  - What are the primary goals of the system? For example, as a user, I would like to:
    - Log in.
    - Post a short message (e.g., a 256-character thought).
    - Read posts from other users.
    - Subscribe to other users.
    - Manage my followers.
    - Read from a personalized feed.
    - Receive notifications.
- Translate these high-level goals into functional requirements.

## Define the Core Data Model:

- Convert the identified functionalities into a structured data model, which typically involves several databases:
  - **User Database:**
    - `id` (primary key)
    - `name`
    - `password`
    - `email`
    - `preferences` (e.g., favorite color)
  - **Tweet Database:**
    - `id` (primary key)
    - `user_id` (foreign key)
    - `content` (e.g., 256-character message)
    - `timestamp`
  - **Subscription Database:**
    - `id` (primary key)
    - `subscriber_id` (foreign key referencing user)
    - `subscribed_to_id` (foreign key referencing user)

## Estimate the Scale and Performance Requirements:

- Understand the potential scale of the system by considering key questions:
  - How many users are expected initially, and what is the potential growth rate?
  - What is the expected number of requests per day, and how does it break down between reads and writes?
  - What is the write-to-read ratio?
  - Are there any budget or timeline constraints that will impact system design?
  - What integrations or external systems will be involved (e.g., authentication, metrics collection, logging)?
  - What are the preferred data formats (e.g., Protocol Buffers, JSON) and communication protocols (e.g., HTTP, gRPC)?
- Determine the required level of availability, consistency, and performance:
  - What are the priorities between consistency and speed? For example:
    - In critical applications (e.g., banking, medical), consistency is paramount.
    - In less critical applications (e.g., social media posts), speed might be prioritized over consistency.
  - Identify potential corner cases:
    - Popular users (e.g., celebrities) may have a much higher number of followers.
    - High-frequency users may post or read a large volume of content daily.

## Analyze the System Requirements and Connect the Dots:

  - Calculate the cost of storing and processing a single piece of data based on the defined data model.
  - Estimate the total volume of data to be handled based on the forecasted user base and activity levels.
  - Use these estimates to determine the capacity of individual components (e.g., servers, databases) and the number of components required to handle the expected load.
  - If past systems or benchmarks are available, use them to guide your capacity planning.
  - If no prior data is available, apply standard scaling techniques and industry best practices.

## Create a High-Level Design:

- Develop a system architecture that satisfies the requirements defined in the previous steps. This should include:
  - The core components of the system (e.g., front-end, back-end, databases, caching layers, messaging queues).
  - The interactions between components.
  - Data flow and storage strategies.
  - Load balancing and scaling strategies.
- Ensure that the design addresses both functional and non-functional requirements.

## Critically Evaluate the Design:

  - **Security:** How will you protect user data and ensure the system is secure?
  - **Scalability:** How will the system handle increased traffic or a growing user base?
  - **Reliability:** How will you ensure the system remains operational? Consider scenarios like:
    - A service failure.
    - A failed request.
    - Database corruption or downtime.
  - **Maintainability:** How easily can changes be made to the system over time?
  - **Performance:** How fast is the system? How will you measure and improve performance?
  - **Cost:** What are the costs of building and maintaining the system?
  - **User Experience:** How intuitive and accessible is the system for users?
  - **Extensibility:** How easy is it to add new features or adapt the system to changing requirements in the future?
