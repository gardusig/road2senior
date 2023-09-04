I have defined some kind of algorithm, still ongoing process. Let's use Twitter as an example:

1. Understand the system by asking the dumbest questions until you can answer the question below
   - What is actually the goal? As a user, I would like to...
     - Login
     - Post a brilliant 256 character thought
     - Read other people's brilliant 256 character thought(s)
     - Subscribe other people
     - Be subscribed by other people
     - Read from a feed
     - Receive notifications
1. Translate previous questions into real data, which is like a bunch of databases
   - User db should have like
     - Id (primary key if sql)
     - Name
     - Password
     - Favorite color
   - Tweet db should have like
     - Id (primary key if sql)
     - UserId (foreign key if sql)
     - Brilliant 256 character thoughts
   - Subscription db
     - TODO
1. Understand the forecasts by asking more dumb questions (try guessing a few answers to keep the conversation fluid)
   - How many users?
   - How many requests per day?
   - Write/read ratio?
   - Budget/Timeline (startups does not allow to evaluate many alternatives)
   - Integrations
     - Auth layer/system
     - Metrics collection
     - Log
   - Preferences:
     - Data formats (monoliths are easier to handle, better consistency)
       - protocol buffers
       - json
       - xml
       - smoke signal
     - Communication (monoliths are easier to handle, better consistency)
       - HTTP
       - gRPC
   - Availability. What is more important, consistency or speed?
     - Considering medical and bank stuff, consistency is very important
     - Brilliant 256 character thoughts? Nah, as quick as possible, no one will die if one disappear
   - What are the corner cases?
     - Famous people should be very interesting to have astronomically more subscribers than avg
     - Creative people write a ton of brilliant 256 character thoughts every day
     - Curious people read a ton of brilliant 256 character thoughts every day
1. Connect the dots. This is the funniest part, you should have all the required data by this time.
   - Given the defined databases at 2, you know approximately the cost of a single piece of data
   - Given the estimations at 3, you know approximately how many pieces of data you must process
   - If you had already created a system
     - There's probably an average number of pieces of data a single system can handle
     - Then it's basic math to discover the amount of systems you need to scale in order to fulfill your requests
   - Otherwise, well this is actually what you are supposed to do at this interview. Wish someone had told me that earlier
1. Design anything that satisfies the goal defined at 1 and is manageable with 4
   - Yeah, creativity must be flowing like a hydropower plant at a waterfall
1. Hm, let's criticize a bit
   - Security: How will you protect your users' data?
   - Scalability: How will you handle increasing traffic?
   - Reliability: How will you ensure that your system is always up and running?
     - What if a service went down?
     - What if a request fail?
     - What if a database gets corrupted?
   - Maintainability: How easy will it be to make changes to your system in the future?
   - Performance: How fast will your system be? How will you measure and improve performance?
   - Cost: How much will it cost to build and maintain your system?
   - User experience: How easy will it be for users to use your system?
   - Extensibility: How easy will it be to add new features to your system in the future?
