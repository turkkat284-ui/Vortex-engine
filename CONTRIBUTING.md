# CONTRIBUTING.md

Thank you! We appreciate your interest in contributing to this project — contributions help the project improve and evolve.

## Code of Conduct
Please be respectful and constructive when communicating in this project. Rude, demeaning, or exclusionary behavior will not be tolerated. If a separate Code of Conduct file exists, follow it.

## How to contribute
1. Fork the repository.
2. Clone your fork locally and add the upstream remote:

```bash
git clone <your-fork-url>
cd Vortex-engine
git remote add upstream https://github.com/turkkat284-ui/Vortex-engine.git
```

3. Create a new branch for your work:

```bash
git checkout -b feature/your-feature-name
# or
git checkout -b fix/your-fix-name
```

4. Keep changes small and focused. Each Pull Request (PR) should address a single goal.
5. Use meaningful commit messages, for example: `feat: short description`, `fix: short description`, `docs: short description`.
6. Add and run tests when applicable:

```bash
go test ./...
```

7. Push your branch to your fork and open a Pull Request against the main repository. In the PR description, explain the purpose of the change, steps to reproduce any bug fixes, and any test notes.

## Code style and quality
- For Go code, run `gofmt`/`goimports` on your changes before committing.
- Follow any configured linter rules (for example, `golangci-lint`) if present.
- Be careful when modifying critical or low-level C code; explain platform and security implications of those changes.

## Security and sensitive information
If you discover a security issue, do not post it publicly. Instead, follow the reporting guidance in SECURITY.md so we can handle the report privately and responsibly.

## Issues and feature requests
- If you find a bug, please open an issue that includes clear reproduction steps and environment details.
- If you have a feature request, describe the use case and include a short draft of a possible solution.

## License
This project is distributed under the license stated in the LICENSE file. When contributing, ensure your changes are compatible with that license.

Thank you — we welcome your contributions!
