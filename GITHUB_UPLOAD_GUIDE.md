# GitHub Upload Guide for Assembly Language Classifier

## Step-by-Step Instructions

### Part 1: Create GitHub Repository

1. **Go to GitHub**
   - Open https://github.com in your browser
   - Log in to your account

2. **Create New Repository**
   - Click the '+' icon in top-right corner
   - Select "New repository"

3. **Repository Settings**
   - **Repository name**: `assembly-language-classifier`
   - **Description**: "ML system to predict source programming languages from assembly code"
   - **Visibility**: Public (so employers can see it)
   - **DO NOT** initialize with README (we already have one)
   - Click "Create repository"

---

### Part 2: Prepare Your Local Project

1. **Open Terminal/Command Prompt**
   - Navigate to your project directory
   ```bash
   cd /path/to/your/project/folder
   ```

2. **Organize Files** (Already done! But verify this structure)
   ```
   assembly-language-classifier/
   ├── FeatureExtractor.h
   ├── FeatureExtractor.cpp
   ├── Classifier.h
   ├── Classifier.cpp
   ├── DatasetGenerator.h
   ├── DatasetGenerator.cpp
   ├── main.cpp
   ├── Makefile
   ├── README.md
   ├── .gitignore
   └── LICENSE
   ```

---

### Part 3: Initialize Git and Upload

**Copy and paste these commands one by one:**

```bash
# Step 1: Initialize git repository
git init

# Step 2: Add all files
git add .

# Step 3: Make first commit
git commit -m "Initial commit: Assembly language classifier in C++"

# Step 4: Rename branch to main (if needed)
git branch -M main

# Step 5: Connect to your GitHub repository
# REPLACE 'yourusername' with your actual GitHub username
git remote add origin https://github.com/yourusername/assembly-language-classifier.git

# Step 6: Push to GitHub
git push -u origin main
```

**If git asks for credentials:**
- Username: Your GitHub username
- Password: Use a Personal Access Token (not your password)
  - Get token at: https://github.com/settings/tokens
  - Click "Generate new token (classic)"
  - Select "repo" scope
  - Copy the token and use it as password

---

### Part 4: Verify Upload

1. Go to your repository URL:
   `https://github.com/yourusername/assembly-language-classifier`

2. You should see all your files listed

3. The README.md will display automatically on the main page

---

### Part 5: Making It Look Professional

#### Add Topics (Tags)
1. On your repository page, click the gear icon next to "About"
2. Add topics: `machine-learning`, `cpp`, `assembly`, `reverse-engineering`, `classification`
3. Click "Save changes"

#### Update Repository Description
1. Click gear icon next to "About"
2. Add description: "C++ ML system predicting source languages from assembly code with 85%+ accuracy"
3. Add website if you have deployed version
4. Click "Save changes"

---

### Part 6: Future Updates

**When you make changes to code:**

```bash
# Step 1: Check what changed
git status

# Step 2: Add changed files
git add .

# Step 3: Commit with meaningful message
git commit -m "Improved feature extraction accuracy"

# Step 4: Push to GitHub
git push
```

**Commit message examples:**
- "Added support for ARM architecture"
- "Fixed bug in opcode counting"
- "Updated README with performance metrics"
- "Improved classification algorithm"

---

## Recommended Repository Structure (Future Expansion)

As you enhance the project, organize it like this:

```
assembly-language-classifier/
├── src/                    # Source code
│   ├── FeatureExtractor.cpp
│   ├── Classifier.cpp
│   └── ...
├── include/               # Header files
│   ├── FeatureExtractor.h
│   └── ...
├── examples/              # Example assembly files
│   ├── sample_c.s
│   └── sample_cpp.s
├── docs/                  # Additional documentation
│   ├── architecture.md
│   └── api_reference.md
├── tests/                 # Unit tests
│   └── test_features.cpp
├── scripts/               # Helper scripts
│   └── compile_dataset.sh
├── Makefile
├── README.md
├── LICENSE
└── .gitignore
```

**To reorganize (do this later when expanding):**

```bash
mkdir src include examples
mv *.cpp src/
mv *.h include/
git add .
git commit -m "Reorganized project structure"
git push
```

---

## Common Issues and Solutions

### Issue 1: "Permission denied (publickey)"
**Solution**: Use HTTPS instead of SSH
```bash
git remote set-url origin https://github.com/yourusername/assembly-language-classifier.git
```

### Issue 2: "Updates were rejected"
**Solution**: Pull first, then push
```bash
git pull origin main --rebase
git push
```

### Issue 3: Files not showing on GitHub
**Solution**: Check .gitignore isn't blocking them
```bash
git status
# If files show as "Untracked", they might be in .gitignore
```

### Issue 4: Large files rejected
**Solution**: Don't commit dataset CSVs (they're in .gitignore already)
- GitHub has 100MB file limit
- Keep datasets local or use Git LFS

---

## Adding to LinkedIn

**After uploading to GitHub:**

1. **LinkedIn Profile**
   - Go to your LinkedIn profile
   - Click "Add profile section" → "Featured"
   - Click "+" → "Link"
   - Paste your GitHub repo URL
   - Title: "Assembly Language Classifier Project"

2. **In Project Section**
   - Add as project with start/end dates
   - Include GitHub link
   - Use the bullet points from your resume

3. **Share as Post**
   ```
   Excited to share my latest project! 🚀

   Built a C++ machine learning system that predicts source programming 
   languages from compiled assembly code with 85%+ accuracy.

   Key achievements:
   ✅ Advanced multi-level feature extraction
   ✅ 7,000+ labeled assembly samples
   ✅ Real-world applications in malware analysis and reverse engineering

   Check it out: [GitHub link]

   #MachineLearning #CPP #ReverseEngineering #NITWarangal
   ```

---

## For Your Resume

**GitHub Link Format:**
```
GitHub: github.com/yourusername/assembly-language-classifier
```

**Or as QR code:**
1. Go to https://www.qr-code-generator.com/
2. Enter your GitHub repo URL
3. Download QR code
4. Add to resume (small, in corner)

---

## Maintenance Tips

1. **Keep README Updated**: Update achievements, metrics, features as you improve
2. **Add Examples**: Include sample assembly files with predictions
3. **Write Comments**: Add inline comments for complex logic
4. **Create Releases**: When you hit milestones (v1.0, v2.0)
5. **Star Your Own Repo**: Looks better when it has at least 1 star 😊

---

## Questions Interviewers Might Ask

**"Can I see the code?"**
- "Yes! It's on my GitHub: github.com/yourusername/assembly-language-classifier"

**"Is this your original work?"**
- "Yes, I designed and implemented the entire C++ system, including the feature extraction algorithms and classification logic"

**"Can you walk me through the code?"**
- Start with main.cpp → show the flow → explain FeatureExtractor → discuss Classifier

---

Good luck with your Oracle interview! 🎯
