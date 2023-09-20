# Summary

- Don't be very technical
- Try using STAR method whenever possible

## STAR method

The STAR method is a structured way of answering behavioral interview questions. It stands for Situation, Task, Action, and Result.

- **Situation**: Describe the context of the situation. This could be a work-related situation, a volunteer experience, or even a personal situation. Be sure to provide enough detail so that the interviewer can understand the situation.
- **Task**: What was your specific goal or responsibility in this situation?
- **Action**: What steps did you take to achieve your goal? Be as specific as possible and highlight the skills and abilities you used.
- **Result**: What was the outcome of your actions? Did you achieve your goal? If so, how? If not, what did you learn from the experience?

## Stories

- Add a title summarizing the story into an impactful message
  - Easy to remember and may catch interviewer attention
    - Like a sensationalist news headline
- Evaluate consistency between stories
  - One must not invalidate another, they should complement each other
    - Beware of writing style, may be easier to remember when following a pattern
    - Do like Sherlock Holmes - be consistent and methodical
- People like numbers, why not make stories sound a bit more palpable?
  - Just add fucking details everywhere
    - Awesome improvement you have made at service X... But, by how much percent?
    - Astonishingly processing time reduction at service Y... By how much, hum?
    - Do like Gabriela Prioli - seasoning with granular refined data and its source
- Remove unnecessary details
  - Still figuring out what is not recommended to speak at an interview
- Tailor each story towards a positive feeling by the end
  - Do like He Man - conclude them with a lessons learned at the end

### Why have I left Orkes?

I was initially happy with the remote contract at the startup. The compensation was much higher than I would have received as a full-time employee in Brazil, and I had the freedom to work from anywhere. However, I soon realized that the company culture was not a good fit for me. They were looking for people who would follow a command-and-control management style, and I am more of a creative thinker who likes to challenge the status quo. This led to many disagreements, and eventually I felt like I was not able to give my full attention to my side business while working at a startup and lost touch with some messages. As a result, the company decided to end the contract after a year and a half.

The company culture changed after the first year. It became more stressful and demanding, and the management team was less supportive. I felt like I was no longer being heard or valued. I also saw how the team was being treated, and I didn't want to be a part of that.

I was disappointed that the management team stopped appearing and recommended to avoid code reviews. I felt like they didn't care about the team or the work we were doing. This made me feel like I was on my own, and it made it difficult to get the support I needed.

I am still proud of the work I did at the startup. I contributed to many open source projects, and I believe that my work has had a positive impact on the community. I learned that it's important to be clear about my expectations and to find a company culture that is a good fit for me.

After the contract ended, I took some vacation after a long time without one. I also made a good deal selling my company, which allowed me to be free to study and get back on the programming track again.

### Why have I left Amazon?

I joined Amazon as a software engineer on the amazon.com.br fba team. I was excited about the opportunity to work for a large and innovative company, but I quickly realized that the role was not a good fit for me.

The projects I was working on were not very challenging or interesting. I was basically adding more layers to existing services in order to be compliant with Brazilian laws. I also felt like I was constantly working on tech debt. I improved the resilience score of a service, but it was then transferred to another team and I was given a new task that was very similar.

In addition, I was not happy with the compensation and benefits. As a Brazilian employee, I was paid in BRL and had to pay high taxes. When I was offered a remote position at a startup in Silicon Valley, I jumped at the chance.

The new position paid me in USD and I had much lower taxes. I was also able to work remotely, which gave me the freedom to live anywhere I wanted. I was much happier with the projects I got to work on and felt like I made a real impact.

Leaving Amazon was clearly the right choice. Even got an equivalent offer from AWS to relocate to Canada, but that's another disappointing story of many suboptimal decisions.

### How I upscaled Amazon FBA invoice services just enough before Black Friday 2021

- Talk about collaborative stuff with neighbor team, to understand forecasted data
- Evaluate TPS
- Evaluate which APIs exist and their usage distribution over time with metrics
  - Get the most used ones
    - Evaluate their costs per request
  - Get the amount of expected requests
    - Divide by the amount a single host can handle
  - It's something like, 10 requests per second
  - If forecasted 500, 50 machines should handle the peak flawlessly

### How I enabled the largest client for Orkes by creating an SDK

- Twilio wanted to use the product, but not only asked but almost set a requirement - to have Go SDK
- Previously to me, only java developers had support

- Then it was the first time I touched Go code
- Ended up creating a client for transforming Go functions into Netflix Conductor workflow task workers
  - It contained a few wrappers for server side HTTP communication through its APIs
    - All generated by using swagger codegen
  - Stored auth token
  - Polled for tasks in batches, starting a separate go routine for each execution
  - Managed amount of available resources, keeping concurrent operations as much to a pre defined limit

### How have I managed all SDKs while at Orkes

- Created Python and Go SDKs
- Improved Java SDK
- Helped to launch C#, JS and Clojure SDKs
- Created integration tests aiming for 100% coverage of relevant code, like most used APIs
- Automated build, test and release through CI/CD at GitHub actions
- Virtually each SDK had automation for:
  - generating HTTP server side API code through swagger codegen
  - run tests automatically on pull request events
  - build package and publish to pkg manager on new release events
- Handle GitHub issues and package versioning
  - Broke compatibility
  - Fixed them overnight
