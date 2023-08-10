- [Summary](#summary)
- [Coding interview](#coding-interview)
- [Behavioral interview](#behavioral-interview)
- [System design interview](#system-design-interview)
- [Ask at the end](#ask-at-the-end)
- [After the interview](#after-the-interview)

# Summary

The interview process generally consists of a few interviews, the goal is to cover each type by documenting a few tricks to prepare and get an offer.

- Be positive and enthusiastic.
  - The interviewer wants to hire someone who is excited about software development
    - Show them that you are passionate about coding!
- Make good impression on the interviewer
  - Make eye contact and smile
  - Sit up straight and speak clearly
  - Be enthusiastic about the opportunity
- Dress appropriately
- Be on time for the interview
- Take the interview seriously.
- Be... yourself :)
  - The interviewer wants to get to know the real you, so don't try to be someone you're not
- Practice, practice, practice!
  - more you practice, more comfortable you will be
    - resources available online and in libraries to help you practice
- Be prepared for anything.
  - The interviewer might ask you a question that you have never seen before
    - Be prepared to think on your feet and to come up with a solution
- Got stuck? Don't be afraid to ask for help
  - The interviewer is there to help you succeed

## Coding interview

This interview generally takes up to an hour, and you are generally expected to solve a few problem(s) using algorithms and data structures.

I think the best result comes from the ease of understanding an interviewer has on why a code exists and how it works. It should look like a reasonable solution and easy to read. You can achieve it by communicating your thought process to the interviewer.

- Ask clarifying questions
  - Essential for making sure that you understand the problem and the expected output
  - Good way to check if you understood the problem
  - Be honest if you already saw the question before
  - Don't be afraid to ask "dumb" questions
    - The dumbest the better, you must be sure of each relevant data
    - The interviewer would rather be asked a question than you get the wrong answer
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
      - Get the greatest range multiplication from an array
        - Sounds like a more complex algorithm
        - Observation: _Zeroes never help at multiplication_
        - So... If you ignore them?
          - Split the array into segments without zeroes
          - Just return the greatest one among them :)
      - Get the winner of a tennis match
        - Problem explains many rules of tennis, sounds complex
        - Observation: _The winner always makes the last turn point_
        - So... If you ignore the others?
          - Just return the last one :)
- Iterate through some examples...
  - Start thinking about potential solutions
    - Be creative
      - There is often more than one way to solve a coding problem
        - Don't be afraid to think outside the box
  - Find corner cases and edge cases that might not be obvious at first
    - Don't underestimate the problem
  - Small examples for easy and quick test
  - Large examples for scalability test
  - Edge cases that test the robustness of your solution
- By this point you should have understood the question and all of its details
  - Trade offs to be considered when choosing a solution
    - Time complexity
    - Space complexity
    - Ease of implementation
    - Correctness
    - Code readability
  - Think about distinct solutions
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
  - use comments to explain your code
    - help the interviewer to understand your code and debug it
  - or invest into pretty well written variable and method names
    - it's faster to write an almost good comment than finding the best name btw
  - easy to understand for both you and the interviewer
  - use proper indentation and spacing
    - makes your code easier to read and understand
- Test the code
  - Test your code against a variety of input/output scenarios
    - Passing by all corner cases and edge cases is probably enough
  - If confused, running it against small input/output scenarios may help
    - Explain what happens over each execution step
      - Actually creating the variables and explaining how their value changes is just fine :)
- Breathe and get back to the problem
  - There is no need for hurry, you've got this

### Practice

I recommend using LeetCode, but smartly: https://neetcode.io/practice. It contains a list of useful problems aiming for the highest interview topic coverage.

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

- Follow-up questions
  - This shows that you're engaged in the conversation and that you're genuinely interested in learning more about the company and the role
  - Maybe related to the problem or ask if happened at a real project
- What are the biggest challenges that the team is facing right now?
- What are the opportunities for growth and development?
- What is the company culture like?
- Why is this position open? Who is expected to fill it?
- How the routine of good performers looks like?
- On-call
  - What is the rotation period? (i.e. Every two weeks)
  - How much time is expected to spend away from standard tasks?
  - Is the team looking for avoiding more tickets?

## After the interview

- Send a thank-you note to the interviewer
