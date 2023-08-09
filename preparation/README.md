- [Summary](#summary)
- [Coding interview](#coding-interview)
- [Behavioral interview](#behavioral-interview)
- [System design interview](#system-design-interview)
- [Ask at the end](#ask-at-the-end)

# Summary

The interview process generally consists of a few interviews, the goal is to cover each type by documenting a few tricks to prepare and get an offer.

## Coding interview

This interview generally takes up to an hour, and you are generally expected to solve a few problem(s) using algorithms and data structures.

Few guides:

- Iterate through some examples
  - Good way to check if you understood the problem
  - Be honest if you already saw the question before
  - Start thinking about potential solutions
  - Try to find corner cases and edge cases that might not be obvious at first
    - Don't underestimate the problem
- Ask clarifying questions
  - Essential for making sure that you understand the problem and the expected output
  - Don't be afraid to ask "dumb" questions
    - The dumbest the better, you must be sure of each relevant data
    - The interviewer would rather you ask a question than get the wrong answer
  - Use examples whenever possible, they will be useful when testing
    - Start a few brain threads to find corner cases in the meantime
  - Try discovering the input/output `size` and input/output `limit range`
    - Quite helpful for determining the time and space complexity of your solution
      - if the input size is very large
        - you might want to use a more efficient algorithm or data structure
    - `size` helps you with time and space complexity, like
      - Length of an array
      - Size of the answer
        - Uncommon, but possible to be asked about all permutations of an array for example
    - `limit range` helps you to tailor your thoughts towards an observational solution
      - Most problems might have a very simple and creative solution
      - Sometimes you can make an observation connecting an input/output condition with the expected answer, like
        - Get the greatest range multiplication from an array _without negative values_
          - Considering what zero makes within a multiplication
            - Zeroes never help, so... If you ignore them?
            - Split the array into segments of positive values
            - Just return the greatest one :)
        - Get the winner of a tennis match _given each turn point winner_
          - Problem might explain many rules of tennis
            - The winner always makes the last turn point, so... If you ignore the others?
              - Just return the last one :)
- By this point you should have understood the question and all of its details
  - Think about distinct solutions and their trade-offs
    - Start by the simplest naive iterative solution and its expected complexity
    - Now its time to understand repeated operations
      - Algorithms and Data structures are useful here
    - There is no "best" solution for every problem
      - The best solution will depend on the specific constraints of the problem
    - Think about different possible solutions
      - Use time and space complexity to compare between them
        - Data structures
          - Size (size complexity)
            - Segment trees consumes more than the input size
          - Query (time complexity)
          - Update (time complexity)
        - Algorithms
        - Runtime (size complexity)
          - Hardly less than input size complexity
            - It's tacky to not at least pass by each value once :)
          - It probably has a well defined worst case complexity
        - Memory (size complexity)
          - Some algorithms might use:
            - more memory
              - like dynamic programming
            - others none
              - like returning the greatest value
- Write good quality code
  - readable, efficient, and well-tested
  - easy to understand for both you and the interviewer
- Test the code
  - Test your code against a variety of input/output scenarios
    - Passing by all corner cases and edge cases is probably enough
  - If confused, running it against small input/output scenarios may help
    - Explain what happens over each execution step
      - Actually creating the variables and explaining how their value changes is just fine :)
    - The interviewer is there to help you
- Breathe and get back to the problem

## Behavioral interview

This interview generally takes up to an hour, and you are generally expected to cover a few of your past experiences. The key point is not to feel ashamed of mistakes, they are quite useful when you have learned a lesson. As you make more distinct mistakes, the better you tend to become.

Few guides:

- Don't be very technical
- Add STAR method explanation link

## System design interview

This interview generally takes up to an hour, and you are generally expected to draw a few things that can be read as a computer system. It does not have to be perfect, otherwise you would be eligible to replace a bunch of people :)

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
     - Brilliant 256 character thoughts
   - Subscription db TODO
1. Understand the expected traffic by asking more dumb questions. Don't forget to guess a few answers to keep the conversation fluid
   - How many users?
   - How many requests per day?
   - Write/read ratio?
   - Budget/Timeline (startups does not allow to evaluate many alternatives)
   - Auth layer/system
   - Metrics collection
   - Log system
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

Few guides:

- Understand the project idea and look at it as a user
- Ask clarifying questions with more details and remove ambiguity
- Define which data should be stored
- Think about how you would organize their storage
- Understand data flow and define APIs to access them
- Draw a few boxes with a general flow from the UI request to the response
- Estimate resource usage and investigate where is the bottleneck
- Discussions may touch:
  - Security
  - Deployment
  - Automation
  - Maintenance
  - Metrics collection
    - Alarms

## Ask at the end

By the end of each interview, you are expected to have around 5 minutes to ask a few questions to the interviewer. It's an opportunity to clarify if you actually likes the company and maybe show interest through an unexpected curiosity.

Few guides:

- On-call
  - What is the rotation period? (i.e. Every two weeks)
  - How much time is expected to spend away from standard tasks?
  - Is the team looking for avoiding more tickets?
- Remote work
  - What are the rules?
  - Does employees receive tool reimbursement?
- Promotion
  - Are there enough projects to support next level experience?
  - What are expectations? And what should be improved to get promoted?
  - How the promotion process looks like?
